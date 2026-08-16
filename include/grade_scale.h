#ifndef GRADE_SCALE_H
#define GRADE_SCALE_H

// Grade reporting rules kept in a single place. The legacy portal repeated
// these boundaries in two files, which is exactly what this unit replaces.
class GradeScale {
public:
    // A strict scale lifts every boundary by five percent. Departments that
    // run the stricter marking policy switch it on from the settings menu.
    explicit GradeScale(bool strict = false);

    double gpaFromPercentage(double percentage) const;
    char letterGrade(double percentage) const;
    bool isPass(double percentage) const;

private:
    bool strict_;
};

#endif
