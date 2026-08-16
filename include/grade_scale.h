#ifndef GRADE_SCALE_H
#define GRADE_SCALE_H

#include <string>

// Grade reporting rules kept in a single place. The legacy portal repeated
// these boundaries in two files, which is exactly what this unit replaces.
class GradeScale {
public:
    double gpaFromPercentage(double percentage) const;

    // Returns the award as text because the scale has half grades: a bare
    // char could not represent A- or B+ and silently rounded them down.
    std::string letterGrade(double percentage) const;
    bool isPass(double percentage) const;
};

#endif
