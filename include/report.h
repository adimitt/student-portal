#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>

// One printed line of the semester report.
struct ReportRow {
    std::string subject;
    int marks = 0;
    std::string grade;
};

// Builds the end of semester report that the office prints for each student.
class SemesterReport {
public:
    void setHeader(const std::string &rollNumber, const std::string &name, int semester);
    void addRow(const std::string &subject, int marks, const std::string &grade);

    int rowCount() const;
    int totalMarks() const;

    // Writes the report to disk. Returns false when the path is not writable.
    bool writeTo(const std::string &path) const;

private:
    std::vector<ReportRow> rows_;
    std::string rollNumber_;
    std::string name_;
    int semester_ = 1;
};

#endif
