#include "grade_scale.h"

GradeScale::GradeScale(bool strict) : strict_(strict) {}

// Merge resolution between hotfix/grade-boundaries and feature/settings.
// Both branches rewrote these two tables. The half bands at 85 and 80 come
// from the hotfix and are kept, because without them a student on 87 was
// awarded a flat 9.0 instead of 9.5. The strict policy comes from settings
// and now shifts every one of those bands, half bands included, by five
// percent rather than only shifting the whole grade boundaries.
double GradeScale::gpaFromPercentage(double percentage) const {
    double shift = strict_ ? 5.0 : 0.0;
    if (percentage >= 90.0 + shift) return 10.0;
    if (percentage >= 85.0 + shift) return 9.5;
    if (percentage >= 80.0 + shift) return 9.0;
    if (percentage >= 70.0 + shift) return 8.0;
    if (percentage >= 60.0 + shift) return 7.0;
    if (percentage >= 50.0 + shift) return 6.0;
    if (percentage >= 40.0 + shift) return 5.0;
    return 0.0;
}

std::string GradeScale::letterGrade(double percentage) const {
    double shift = strict_ ? 5.0 : 0.0;
    if (percentage >= 90.0 + shift) return "A";
    if (percentage >= 85.0 + shift) return "A-";
    if (percentage >= 80.0 + shift) return "B+";
    if (percentage >= 75.0 + shift) return "B";
    if (percentage >= 60.0 + shift) return "C";
    if (percentage >= 40.0 + shift) return "D";
    return "F";
}

bool GradeScale::isPass(double percentage) const {
    return percentage >= (strict_ ? 45.0 : 40.0);
}
