#include "settings.h"

#include "input_utils.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

const Settings &SettingsStore::current() const {
    return settings_;
}

void SettingsStore::apply(const Settings &settings) {
    settings_ = settings;
}

bool SettingsStore::usesStrictScale() const {
    return settings_.gradeScale == "strict";
}

bool SettingsStore::parseBool(const std::string &value) {
    return value == "true" || value == "1" || value == "on" || value == "yes";
}

bool SettingsStore::load(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "No config at " << path << ", keeping defaults.\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t equals = line.find('=');
        if (equals == std::string::npos) {
            std::cout << "Ignoring config line without '=': " << line << "\n";
            continue;
        }

        std::string key = line.substr(0, equals);
        std::string value = line.substr(equals + 1);

        if (key == "grade_scale") {
            settings_.gradeScale = value;
        } else if (key == "round_percentage") {
            settings_.roundPercentage = parseBool(value);
        } else if (key == "decimal_places") {
            settings_.decimalPlaces = std::atoi(value.c_str());
        } else if (key == "show_bar_chart") {
            settings_.showBarChart = parseBool(value);
        } else {
            std::cout << "Unknown setting '" << key << "', skipped.\n";
        }
    }
    return true;
}

bool SettingsStore::save(const std::string &path) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cout << "Could not write settings to " << path << ".\n";
        return false;
    }

    file << "# Portal settings, rewritten on save.\n";
    file << "grade_scale=" << settings_.gradeScale << "\n";
    file << "round_percentage=" << (settings_.roundPercentage ? "true" : "false") << "\n";
    file << "decimal_places=" << settings_.decimalPlaces << "\n";
    file << "show_bar_chart=" << (settings_.showBarChart ? "true" : "false") << "\n";
    return true;
}

void SettingsStore::runMenu(const std::string &configPath) {
    int changed = 0;

    while (true) {
        renderCurrent();
        std::cout << "\n1. Switch grade scale (ten-point / strict)\n"
                  << "2. Toggle percentage rounding\n"
                  << "3. Toggle the subject bar chart\n"
                  << "4. Save and return\n"
                  << "0. Return without saving\n"
                  << "Select an option: ";

        int choice = input_utils::readMenuChoice(0, 4);
        if (choice == 0) {
            std::cout << "Left settings unchanged on disk.\n";
            return;
        }
        if (choice == 4) {
            save(configPath);
            std::cout << changed << (changed == 1 ? " setting" : " settings")
                      << " written to " << configPath << ".\n";
            return;
        }
        if (choice == 1) {
            settings_.gradeScale = usesStrictScale() ? "ten-point" : "strict";
        } else if (choice == 2) {
            settings_.roundPercentage = !settings_.roundPercentage;
        } else {
            settings_.showBarChart = !settings_.showBarChart;
        }
        ++changed;
    }
}

void SettingsStore::renderCurrent() const {
    std::cout << "\n--- Settings ---\n";
    std::cout << "Grade scale     : " << settings_.gradeScale << "\n";
    std::cout << "Round percentage: " << (settings_.roundPercentage ? "on" : "off") << "\n";
    std::cout << "Decimal places  : " << settings_.decimalPlaces << "\n";
    std::cout << "Bar chart       : " << (settings_.showBarChart ? "shown" : "hidden") << "\n";
}
