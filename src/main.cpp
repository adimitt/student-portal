#include "calculator.h"
#include "input_utils.h"

#include <iomanip>
#include <iostream>
#include <vector>

namespace {

void showMenu() {
    std::cout << "\n=== Student Portal ===\n"
              << "1. Marks calculator\n"
              << "0. Exit\n"
              << "Select an option: ";
}

void runMarksCalculator() {
    Calculator calc;

    std::cout << "Number of subjects (1-10): ";
    int subjects = input_utils::readMenuChoice(1, 10);
    std::vector<int> marks = input_utils::readMarks(subjects, 100);

    double pct = calc.percentage(marks, 100);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total      : " << calc.total(marks) << " / " << subjects * 100 << "\n";
    std::cout << "Percentage : " << pct << " %\n";
    std::cout << "GPA        : " << calc.gpaFromPercentage(pct) << "\n";
    std::cout << "Grade      : " << calc.letterGrade(pct) << "\n";
}

}

int main() {
    std::cout << "Student portal starting up.\n";

    while (true) {
        showMenu();
        int choice = input_utils::readMenuChoice(0, 1);
        if (choice == 0) {
            std::cout << "Signing off.\n";
            break;
        }
        runMarksCalculator();
    }
    return 0;
}
