#include "report.h"

#include <fstream>
#include <iostream>

void SemesterReport::setHeader(const std::string &rollNumber,
                               const std::string &name,
                               int semester) {
    rollNumber_ = rollNumber;
    name_ = name;
    semester_ = semester;
}

void SemesterReport::addRow(const std::string &subject, int marks,
                            const std::string &grade) {
    ReportRow row;
    row.subject = subject;
    row.marks = marks;
    row.grade = grade;
    rows_.push_back(row);
}

int SemesterReport::rowCount() const {
    return static_cast<int>(rows_.size());
}

int SemesterReport::totalMarks() const {
    int sum = 0;
    for (const ReportRow &row : rows_) {
        sum += row.marks;
    }
    return sum;
}

bool SemesterReport::writeTo(const std::string &path) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cout << "Could not write the report to " << path << ".\n";
        return false;
    }

    file << "Semester report\n";
    file << "Roll number: " << rollNumber_ << "\n";
    file << "Name       : " << name_ << "\n";
    file << "Semester   : " << semester_ << "\n\n";

    for (const ReportRow &row : rows_) {
        file << row.subject << "," << row.marks << "," << row.grade << "\n";
    }

    file << "\nTotal: " << totalMarks() << " over " << rowCount() << " subject(s)\n";
    std::cout << "Report written to " << path << ".\n";
    return true;
}
