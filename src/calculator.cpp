#include "calculator.h"

double Calculator::add(double a, double b) const {
    return a + b;
}

double Calculator::subtract(double a, double b) const {
    return a - b;
}

double Calculator::multiply(double a, double b) const {
    return a * b;
}

bool Calculator::divide(double a, double b, double &out) const {
    if (b == 0.0) {
        return false;
    }
    out = a / b;
    return true;
}

int Calculator::total(const std::vector<int> &marks) const {
    int sum = 0;
    for (int m : marks) {
        sum += m;
    }
    return sum;
}

double Calculator::percentage(const std::vector<int> &marks, int maxPerSubject) const {
    if (marks.empty() || maxPerSubject <= 0) {
        return 0.0;
    }
    double obtained = static_cast<double>(total(marks));
    double possible = static_cast<double>(marks.size()) * maxPerSubject;
    return (obtained / possible) * 100.0;
}

double Calculator::weightedAverage(const std::vector<double> &marks,
                                   const std::vector<double> &weights) const {
    if (marks.size() != weights.size() || marks.empty()) {
        return 0.0;
    }
    double weighted = 0.0;
    double weightSum = 0.0;
    for (size_t i = 0; i < marks.size(); ++i) {
        weighted += marks[i] * weights[i];
        weightSum += weights[i];
    }
    return weightSum == 0.0 ? 0.0 : weighted / weightSum;
}

// Ten point scale. One grade point per ten percent above the pass mark.
double Calculator::gpaFromPercentage(double percentage) const {
    if (percentage >= 90.0) return 10.0;
    if (percentage >= 80.0) return 9.0;
    if (percentage >= 70.0) return 8.0;
    if (percentage >= 60.0) return 7.0;
    if (percentage >= 50.0) return 6.0;
    if (percentage >= 40.0) return 5.0;
    return 0.0;
}

char Calculator::letterGrade(double percentage) const {
    if (percentage >= 90.0) return 'A';
    if (percentage >= 75.0) return 'B';
    if (percentage >= 60.0) return 'C';
    if (percentage >= 40.0) return 'D';
    return 'F';
}
