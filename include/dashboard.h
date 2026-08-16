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

    // Attendance is tracked separately from marks because the institute
    // rule is a straight percentage of classes held.
    void setAttendance(int classesAttended, int classesHeld);
    double attendancePercentage() const;
    bool meetsAttendanceRule() const;

    void renderSummary() const;
    void renderAttendancePanel() const;

    static const int requiredAttendance = 75;

private:
    std::vector<SubjectRecord> subjects_;
    int attended_ = 0;
    int held_ = 0;
};

#endif
