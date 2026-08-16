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
