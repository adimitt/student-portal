#ifndef GRADE_SCALE_H
#define GRADE_SCALE_H

// Grade reporting rules kept in a single place. The legacy portal repeated
// these boundaries in two files, which is exactly what this unit replaces.
class GradeScale {
public:
    double gpaFromPercentage(double percentage) const;
    char letterGrade(double percentage) const;
    bool isPass(double percentage) const;
};

#endif
