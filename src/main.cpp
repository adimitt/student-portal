#include "auth.h"
#include "calculator.h"
#include "dashboard.h"
#include "grade_scale.h"
#include "input_utils.h"
#include "profile.h"
#include "settings.h"

#include <iomanip>
#include <iostream>
#include <vector>

namespace {

const char *kConfigPath = "data/portal.conf";

void showMenu(const Session &session) {
    std::cout << "\n=== Student Portal (" << session.username << ") ===\n"
              << "1. Marks calculator\n"
              << "2. View and edit profile\n"
              << "3. Dashboard\n"
              << "4. Settings\n"
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

void runProfileScreen(ProfileBook &book, const Session &session) {
    StudentProfile *mine = book.findByRollMutable(session.username);
    if (mine == nullptr) {
        std::cout << "No profile is linked to " << session.username << ".\n";
        return;
    }

    book.render(*mine);
    std::cout << "\nEdit this profile? 1 = yes, 0 = no: ";
    if (input_utils::readMenuChoice(0, 1) == 1) {
        book.editInteractive(*mine);
        book.render(*mine);
    }
}

void runDashboard(Dashboard &board) {
    board.refresh();

    std::cout << "\nAdd a grade entry? 1 = yes, 0 = no: ";
    if (input_utils::readMenuChoice(0, 1) == 1) {
        std::cout << "Subject name: ";
        std::string subject;
        std::getline(std::cin, subject);
        std::cout << "Marks out of 100: ";
        int marks = input_utils::readMenuChoice(0, 100);
        board.recordGradeEntry(subject, marks, 100);
    }
}

Dashboard seededDashboard() {
    Dashboard board;
    board.addSubject("Maths", 78);
    board.addSubject("Physics", 65);
    board.addSubject("Chemistry", 91);
    board.addSubject("English", 54);
    board.addSubject("CS", 83);
    board.setAttendance(58, 72);
    return board;
}

}

int main() {
    std::cout << "Student portal starting up.\n";

    SettingsStore settings;
    settings.load(kConfigPath);

    ProfileBook book;
    book.loadFromFile("data/profiles.txt");
    Dashboard board = seededDashboard();

    AuthStore store;
    Session session = store.authenticate();
    if (!session.active) {
        std::cout << "Exiting, authentication failed.\n";
        return 1;
    }

    while (true) {
        showMenu(session);
        int choice = input_utils::readMenuChoice(0, 4);
        if (choice == 0) {
            std::cout << "Signing off, " << session.username << ".\n";
            break;
        }
        if (choice == 1) {
            runMarksCalculator();
        } else if (choice == 2) {
            runProfileScreen(book, session);
        } else if (choice == 3) {
            runDashboard(board);
        } else {
            settings.runMenu(kConfigPath);
        }
    }
    return 0;
}
