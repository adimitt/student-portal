#include "profile.h"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

ProfileBook::ProfileBook() {
    profiles_.push_back({"2026201055", "Aditya Mittal", "M.Tech CSE",
                         "aditya.mittal@students.example.edu", 3});
    profiles_.push_back({"2026201042", "Rhea Nair", "M.Tech CSE",
                         "rhea.nair@students.example.edu", 3});
    profiles_.push_back({"2026201078", "Karan Bose", "M.Tech ECE",
                         "karan.bose@students.example.edu", 2});
}

const std::vector<StudentProfile> &ProfileBook::all() const {
    return profiles_;
}

const StudentProfile *ProfileBook::findByRoll(const std::string &rollNumber) const {
    for (const StudentProfile &profile : profiles_) {
        if (profile.rollNumber == rollNumber) {
            return &profile;
        }
    }
    return nullptr;
}

StudentProfile *ProfileBook::findByRollMutable(const std::string &rollNumber) {
    for (StudentProfile &profile : profiles_) {
        if (profile.rollNumber == rollNumber) {
            return &profile;
        }
    }
    return nullptr;
}

size_t ProfileBook::size() const {
    return profiles_.size();
}

bool ProfileBook::loadFromFile(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "No profile data at " << path << ", using seeded records.\n";
        return false;
    }

    std::vector<StudentProfile> loaded;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::stringstream stream(line);
        std::string field;
        std::vector<std::string> fields;
        while (std::getline(stream, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() != 5) {
            std::cout << "Skipping malformed profile line: " << line << "\n";
            continue;
        }

        StudentProfile profile;
        profile.rollNumber = fields[0];
        profile.name = fields[1];
        profile.programme = fields[2];
        profile.email = fields[3];
        profile.semester = std::atoi(fields[4].c_str());
        loaded.push_back(profile);
    }

    if (!loaded.empty()) {
        profiles_ = loaded;
    }
    return true;
}

void ProfileBook::render(const StudentProfile &profile) const {
    std::cout << std::left;
    std::cout << std::setw(labelWidth) << "Roll no"   << ": " << profile.rollNumber << "\n";
    std::cout << std::setw(labelWidth) << "Name"      << ": " << profile.name << "\n";
    std::cout << std::setw(labelWidth) << "Programme" << ": " << profile.programme << "\n";
    std::cout << std::setw(labelWidth) << "Semester"  << ": " << profile.semester << "\n";
    std::cout << std::setw(labelWidth) << "Email"     << ": " << profile.email << "\n";
    std::cout << std::right;
}

void ProfileBook::renderAll() const {
    for (const StudentProfile &profile : profiles_) {
        std::cout << "------------------------------\n";
        render(profile);
    }
    std::cout << "------------------------------\n";
    std::cout << profiles_.size() << " profile(s) on record.\n";
}

bool ProfileBook::isValidEmail(const std::string &email) {
    size_t at = email.find('@');
    if (at == std::string::npos || at == 0) {
        return false;
    }
    size_t dot = email.find('.', at);
    return dot != std::string::npos && dot + 1 < email.size();
}

bool ProfileBook::isValidSemester(int semester) {
    return semester >= 1 && semester <= 8;
}

int ProfileBook::editInteractive(StudentProfile &profile) const {
    std::string entry;
    int changed = 0;

    std::cout << "Leave a field blank to keep the current value.\n";

    std::cout << "Name [" << profile.name << "]: ";
    std::getline(std::cin, entry);
    if (!entry.empty()) {
        profile.name = entry;
        ++changed;
    }

    std::cout << "Programme [" << profile.programme << "]: ";
    std::getline(std::cin, entry);
    if (!entry.empty()) {
        profile.programme = entry;
        ++changed;
    }

    std::cout << "Email [" << profile.email << "]: ";
    std::getline(std::cin, entry);
    if (!entry.empty()) {
        if (isValidEmail(entry)) {
            profile.email = entry;
            ++changed;
        } else {
            std::cout << "  rejected, an email needs a name, an @ and a domain.\n";
        }
    }

    std::cout << "Semester [" << profile.semester << "]: ";
    std::getline(std::cin, entry);
    if (!entry.empty()) {
        int semester = std::atoi(entry.c_str());
        if (isValidSemester(semester)) {
            profile.semester = semester;
            ++changed;
        } else {
            std::cout << "  rejected, semester must be between 1 and 8.\n";
        }
    }

    std::cout << changed << " field(s) updated.\n";
    return changed;
}
