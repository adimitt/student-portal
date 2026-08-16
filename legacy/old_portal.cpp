// Legacy student portal - single file version.
// Kept for reference during the overhaul. Do not extend this file;
// new work belongs in src/ with proper headers.

#include <iostream>
#include <string>

int marks[5] = {78, 65, 91, 54, 83};
std::string subs[5] = {"Maths", "Physics", "Chemistry", "English", "CS"};

int total_marks() {
    int t = 0;
    for (int i = 0; i < 5; i++) t += marks[i];
    return t;
}

char grade_of(int m) {
    if (m >= 90) return 'A';
    if (m >= 75) return 'B';
    if (m >= 60) return 'C';
    if (m >= 40) return 'D';
    return 'F';
}

int main() {
    std::cout << "=== Student Portal (legacy build) ===\n";
    for (int i = 0; i < 5; i++) {
        std::cout << subs[i] << "\t" << marks[i] << "\t" << grade_of(marks[i]) << "\n";
    }
    int t = total_marks();
    std::cout << "Total: " << t << "/500\n";
    std::cout << "Percentage: " << (t / 5.0) << "%\n";
    return 0;
}
