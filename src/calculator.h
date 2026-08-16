#ifndef CALCULATOR_H
#define CALCULATOR_H

// Arithmetic used by the marks calculator screen of the portal.
class Calculator {
public:
    double add(double a, double b) const;
    double subtract(double a, double b) const;
    double multiply(double a, double b) const;

    // Division is checked: returns false and leaves out untouched when
    // the divisor is zero, so the caller can report it instead of trapping.
    bool divide(double a, double b, double &out) const;
};

#endif
