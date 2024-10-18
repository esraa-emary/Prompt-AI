// ================================================ Compilot =======================================================

#include "Polynomial.h"

// Default constructor
Polynomial::Polynomial() : coeffs({0}) {}

// Constructor with coefficients
Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {}

// Copy constructor
Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

// Destructor
Polynomial::~Polynomial() {}

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

// Addition
Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < coeffs.size()) result[i] += coeffs[i];
        if (i < other.coeffs.size()) result[i] += other.coeffs[i];
    }
    return Polynomial(result);
}

// Subtraction
Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < coeffs.size()) result[i] += coeffs[i];
        if (i < other.coeffs.size()) result[i] -= other.coeffs[i];
    }
    return Polynomial(result);
}

// Multiplication
Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(result);
}

// Equality operator
bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

// Output operator
ostream& operator<<(ostream& out, const Polynomial& poly) {
    bool first = true;
    for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            if (!first && poly.coeffs[i] > 0) out << " + ";
            if (first || poly.coeffs[i] < 0) out << poly.coeffs[i];
            else if (poly.coeffs[i] > 0) out << poly.coeffs[i];
            if (i > 0) out << "x^" << i;
            first = false;
        }
    }
    return out;
}

// Degree of the polynomial
int Polynomial::degree() const {
    return coeffs.size() - 1;
}

// Evaluate the polynomial at x
double Polynomial::evaluate(double x) const {
    double result = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

// Compose this polynomial with q
Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result({0});
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = q * result + Polynomial({coeffs[i]});
    }
    return result;
}

// Derivative of the polynomial
Polynomial Polynomial::derivative() const {
    if (coeffs.size() <= 1) return Polynomial(vector<double>{0});
    vector<double> result(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i) {
        result[i - 1] = coeffs[i] * i;
    }
    return Polynomial(result);
}

// Indefinite integral of the polynomial
Polynomial Polynomial::integral() const {
    vector<double> result(coeffs.size() + 1, 0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(result);
}

// Definite integral from x1 to x2
double Polynomial::integral(double x1, double x2) const {
    Polynomial integral_poly = integral();
    return integral_poly.evaluate(x2) - integral_poly.evaluate(x1);
}

double Polynomial::getRoot(double guess, double tolerance, int maxIter) {
    double x0 = guess;
    for (int i = 0; i < maxIter; ++i) {
        double y = evaluate(x0);
        double y_prime = derivative().evaluate(x0);

        // Check for a very small derivative to avoid division by zero
        if (abs(y_prime) < tolerance) break;

        double x1 = x0 - y / y_prime;

        // If the new guess is very close to the old guess, stop iterating
        if (abs(x1 - x0) < tolerance) {
            // Check if the found root is indeed real
            if (abs(evaluate(x1)) < tolerance) {
                return x1;
            } else {
                break; // If not a real root, break the loop
            }
        }

        x0 = x1;
    }

    return x0; // Return the best guess
}


// Set the coefficients
void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
}

// Get the coefficient of a specific degree
double Polynomial::getCoefficient(int degree) const {
    return (degree < coeffs.size()) ? coeffs[degree] : 0;
}
