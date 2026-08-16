#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <vector>

// One row of the semester mark sheet.
struct SubjectRecord {
    std::string name;
    int marks = 0;
    int maxMarks = 100;
};

// Aggregates the semester mark sheet into the numbers shown on screen.
class Dashboard {
public:
    void addSubject(const std::string &name, int marks, int maxMarks = 100);

    int totalObtained() const;
    int totalPossible() const;
    double overallPercentage() const;

    void renderSummary() const;

private:
    std::vector<SubjectRecord> subjects_;
};

#endif
