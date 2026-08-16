#include "profile.h"

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
