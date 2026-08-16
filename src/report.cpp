#include "report.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

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

std::string SemesterReport::renderPlainText() const {
    std::ostringstream out;
    std::string rule(pageWidth, '=');
    std::string thin(pageWidth, '-');

    out << rule << "\n";
    out << std::left << std::setw(pageWidth) << "SEMESTER REPORT" << "\n";
    out << rule << "\n";
    out << std::left << std::setw(14) << "Roll number" << ": " << rollNumber_ << "\n";
    out << std::left << std::setw(14) << "Name" << ": " << name_ << "\n";
    out << std::left << std::setw(14) << "Semester" << ": " << semester_ << "\n";
    out << thin << "\n";

    out << std::left << std::setw(26) << "SUBJECT"
        << std::right << std::setw(12) << "MARKS"
        << std::setw(12) << "GRADE" << "\n";
    out << thin << "\n";

    for (const ReportRow &row : rows_) {
        out << std::left << std::setw(26) << row.subject
            << std::right << std::setw(12) << row.marks
            << std::setw(12) << row.grade << "\n";
    }

    out << thin << "\n";
    out << std::left << std::setw(26) << "TOTAL"
        << std::right << std::setw(12) << totalMarks()
        << std::setw(12) << rowCount() << "\n";
    out << rule << "\n";

    return out.str();
}

bool SemesterReport::writeTo(const std::string &path) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cout << "Could not write the report to " << path << ".\n";
        return false;
    }

    file << renderPlainText();
    std::cout << "Report written to " << path << ".\n";
    return true;
}
