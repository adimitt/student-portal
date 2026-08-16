#include "grade_scale.h"

GradeScale::GradeScale(bool strict) : strict_(strict) {}

// Ten point scale: one grade point for every ten percent above the pass mark.
// Under the strict policy every boundary sits five percent higher.
double GradeScale::gpaFromPercentage(double percentage) const {
    double shift = strict_ ? 5.0 : 0.0;
    if (percentage >= 90.0 + shift) return 10.0;
    if (percentage >= 80.0 + shift) return 9.0;
    if (percentage >= 70.0 + shift) return 8.0;
    if (percentage >= 60.0 + shift) return 7.0;
    if (percentage >= 50.0 + shift) return 6.0;
    if (percentage >= 40.0 + shift) return 5.0;
    return 0.0;
}

char GradeScale::letterGrade(double percentage) const {
    double shift = strict_ ? 5.0 : 0.0;
    if (percentage >= 90.0 + shift) return 'A';
    if (percentage >= 75.0 + shift) return 'B';
    if (percentage >= 60.0 + shift) return 'C';
    if (percentage >= 40.0 + shift) return 'D';
    return 'F';
}

bool GradeScale::isPass(double percentage) const {
    return percentage >= (strict_ ? 45.0 : 40.0);
}
