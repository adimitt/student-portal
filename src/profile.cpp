#include "profile.h"

#include <iomanip>
#include <iostream>

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

size_t ProfileBook::size() const {
    return profiles_.size();
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
