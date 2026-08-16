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

    // Subject wise marks drawn as a bar chart, scaled so the longest bar
    // fills chartWidth columns.
    void renderBarChart() const;

    // Adds a row and immediately redraws every panel, so the totals on
    // screen can never lag behind the marks that were just entered.
    void recordGradeEntry(const std::string &name, int marks, int maxMarks = 100);
    void refresh() const;

    // Writes the summary as CSV so it can be opened in a spreadsheet.
    // Returns false when the destination cannot be written.
    bool exportCsv(const std::string &path) const;

    static const int requiredAttendance = 75;
    static const int chartWidth = 40;

private:
    std::vector<SubjectRecord> subjects_;
    int attended_ = 0;
    int held_ = 0;
};

#endif
