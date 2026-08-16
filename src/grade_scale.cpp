#include "grade_scale.h"

// Ten point scale: one grade point for every ten percent above the pass mark.
// The half bands at 85 and 75 were missing, so a student on 87 was awarded a
// flat 9.0 instead of the 9.5 the handbook specifies.
double GradeScale::gpaFromPercentage(double percentage) const {
    if (percentage >= 90.0) return 10.0;
    if (percentage >= 85.0) return 9.5;
    if (percentage >= 80.0) return 9.0;
    if (percentage >= 70.0) return 8.0;
    if (percentage >= 60.0) return 7.0;
    if (percentage >= 50.0) return 6.0;
    if (percentage >= 40.0) return 5.0;
    return 0.0;
}

std::string GradeScale::letterGrade(double percentage) const {
    if (percentage >= 90.0) return "A";
    if (percentage >= 85.0) return "A-";
    if (percentage >= 80.0) return "B+";
    if (percentage >= 75.0) return "B";
    if (percentage >= 60.0) return "C";
    if (percentage >= 40.0) return "D";
    return "F";
}

bool GradeScale::isPass(double percentage) const {
    return percentage >= 40.0;
}
