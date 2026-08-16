#include "dashboard.h"

#include <iomanip>
#include <iostream>

void Dashboard::addSubject(const std::string &name, int marks, int maxMarks) {
    SubjectRecord record;
    record.name = name;
    record.marks = marks;
    record.maxMarks = maxMarks;
    subjects_.push_back(record);
}

int Dashboard::totalObtained() const {
    int sum = 0;
    for (const SubjectRecord &record : subjects_) {
        sum += record.marks;
    }
    return sum;
}

int Dashboard::totalPossible() const {
    int sum = 0;
    for (const SubjectRecord &record : subjects_) {
        sum += record.maxMarks;
    }
    return sum;
}

double Dashboard::overallPercentage() const {
    int possible = totalPossible();
    if (possible == 0) {
        return 0.0;
    }
    return (static_cast<double>(totalObtained()) / possible) * 100.0;
}

void Dashboard::renderSummary() const {
    std::cout << "\n--- Semester summary ---\n";
    std::cout << std::left << std::setw(14) << "Subject"
              << std::right << std::setw(8) << "Marks"
              << std::setw(8) << "Max" << "\n";

    for (const SubjectRecord &record : subjects_) {
        std::cout << std::left << std::setw(14) << record.name
                  << std::right << std::setw(8) << record.marks
                  << std::setw(8) << record.maxMarks << "\n";
    }

    std::cout << std::left << std::setw(14) << "TOTAL"
              << std::right << std::setw(8) << totalObtained()
              << std::setw(8) << totalPossible() << "\n";
    std::cout << std::fixed << std::setprecision(2)
              << "Overall: " << overallPercentage() << " %\n";
}
