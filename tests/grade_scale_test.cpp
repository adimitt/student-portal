// Boundary cases for the ten point scale.
//
// Not part of the portal build, the Makefile only globs src/*.cpp.
// Compile it on its own with:
//   g++ -std=c++17 -Iinclude tests/grade_scale_test.cpp src/grade_scale.cpp \
//       -o bin/grade_scale_test && ./bin/grade_scale_test

#include "grade_scale.h"

#include <cassert>
#include <iostream>

int main() {
    GradeScale scale;

    // Exactly on a boundary must award the higher band.
    assert(scale.letterGrade(90.0) == "A");
    assert(scale.letterGrade(85.0) == "A-");
    assert(scale.letterGrade(80.0) == "B+");
    assert(scale.letterGrade(75.0) == "B");

    // Just below a boundary must drop to the band underneath. These are the
    // four cases that were wrong before the half bands were added.
    assert(scale.letterGrade(89.9) == "A-");
    assert(scale.letterGrade(84.9) == "B+");
    assert(scale.letterGrade(79.9) == "B");
    assert(scale.letterGrade(74.9) == "C");

    // Pass mark and the bottom of the scale.
    assert(scale.letterGrade(40.0) == "D");
    assert(scale.letterGrade(39.9) == "F");
    assert(scale.isPass(40.0));
    assert(!scale.isPass(39.9));

    // GPA half steps line up with the letter bands.
    assert(scale.gpaFromPercentage(90.0) == 10.0);
    assert(scale.gpaFromPercentage(87.0) == 9.5);
    assert(scale.gpaFromPercentage(85.0) == 9.5);
    assert(scale.gpaFromPercentage(84.9) == 9.0);

    std::cout << "grade_scale: all boundary cases passed\n";
    return 0;
}
