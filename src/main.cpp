#include "auth.h"
#include "calculator.h"
#include "grade_scale.h"
#include "input_utils.h"

#include <iomanip>
#include <iostream>
#include <vector>

namespace {

void showMenu(const Session &session) {
    std::cout << "\n=== Student Portal (" << session.username << ") ===\n"
              << "1. Marks calculator\n"
              << "0. Sign out\n"
              << "Select an option: ";
}

void runMarksCalculator() {
    Calculator calc;
    GradeScale scale;

    std::cout << "Number of subjects (1-10): ";
    int subjects = input_utils::readMenuChoice(1, 10);
    std::vector<int> marks = input_utils::readMarks(subjects, 100);

    double pct = calc.percentage(marks, 100);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total      : " << calc.total(marks) << " / " << subjects * 100 << "\n";
    std::cout << "Percentage : " << pct << " %\n";
    std::cout << "GPA        : " << scale.gpaFromPercentage(pct) << "\n";
    std::cout << "Grade      : " << scale.letterGrade(pct) << "\n";
    std::cout << "Result     : " << (scale.isPass(pct) ? "PASS" : "FAIL") << "\n";
}

}

int main() {
    std::cout << "Student portal starting up.\n";

    AuthStore store;
    Session session = store.authenticate();
    if (!session.active) {
        std::cout << "Exiting, authentication failed.\n";
        return 1;
    }

    while (true) {
        showMenu(session);
        int choice = input_utils::readMenuChoice(0, 1);
        if (choice == 0) {
            std::cout << "Signing off, " << session.username << ".\n";
            break;
        }
        runMarksCalculator();
    }
    return 0;
}
