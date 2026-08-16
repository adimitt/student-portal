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

void Dashboard::setAttendance(int classesAttended, int classesHeld) {
    if (classesHeld < 0 || classesAttended < 0 || classesAttended > classesHeld) {
        std::cout << "Attendance figures rejected, attended cannot exceed held.\n";
        return;
    }
    attended_ = classesAttended;
    held_ = classesHeld;
}

double Dashboard::attendancePercentage() const {
    if (held_ == 0) {
        return 0.0;
    }
    return (static_cast<double>(attended_) / held_) * 100.0;
}

bool Dashboard::meetsAttendanceRule() const {
    return attendancePercentage() >= requiredAttendance;
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

void Dashboard::renderAttendancePanel() const {
    std::cout << "\n--- Attendance ---\n";
    std::cout << "Classes held     : " << held_ << "\n";
    std::cout << "Classes attended : " << attended_ << "\n";
    std::cout << std::fixed << std::setprecision(2)
              << "Attendance       : " << attendancePercentage() << " %\n";
    std::cout << "Requirement      : " << requiredAttendance << " %\n";
    std::cout << "Status           : "
              << (meetsAttendanceRule() ? "eligible for exams"
                                        : "short of attendance") << "\n";
}

void Dashboard::renderBarChart() const {
    std::cout << "\n--- Subject wise marks ---\n";
    if (subjects_.empty()) {
        std::cout << "Nothing to plot yet.\n";
        return;
    }

    for (const SubjectRecord &record : subjects_) {
        int filled = 0;
        if (record.maxMarks > 0) {
            filled = (record.marks * chartWidth) / record.maxMarks;
        }

        std::cout << std::left << std::setw(14) << record.name << "|";
        for (int column = 0; column < chartWidth; ++column) {
            std::cout << (column < filled ? '#' : ' ');
        }
        std::cout << "| " << record.marks << "\n";
    }
}

void Dashboard::recordGradeEntry(const std::string &name, int marks, int maxMarks) {
    addSubject(name, marks, maxMarks);
    std::cout << "Recorded " << marks << "/" << maxMarks << " for " << name << ".\n";
    refresh();
}

void Dashboard::refresh() const {
    renderSummary();
    renderAttendancePanel();
    renderBarChart();
}
