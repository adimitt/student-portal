#include "settings.h"

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

void SettingsStore::renderCurrent() const {
    std::cout << "\n--- Settings ---\n";
    std::cout << "Grade scale     : " << settings_.gradeScale << "\n";
    std::cout << "Round percentage: " << (settings_.roundPercentage ? "on" : "off") << "\n";
    std::cout << "Decimal places  : " << settings_.decimalPlaces << "\n";
    std::cout << "Bar chart       : " << (settings_.showBarChart ? "shown" : "hidden") << "\n";
}
