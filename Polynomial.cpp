// ================================================= Chat GPT ==========================================================

#include "Polynomial.h"
#include <stdexcept>
#include <cmath>

// Default constructor
Polynomial::Polynomial() : coeffs(1, 0) {}

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

// Addition of two polynomials
Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> result_coeffs(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i)
        result_coeffs[i] += coeffs[i];
    for (size_t i = 0; i < other.coeffs.size(); ++i)
        result_coeffs[i] += other.coeffs[i];
    return Polynomial(result_coeffs);
}

// Subtraction of two polynomials
Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> result_coeffs(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i)
        result_coeffs[i] += coeffs[i];
    for (size_t i = 0; i < other.coeffs.size(); ++i)
        result_coeffs[i] -= other.coeffs[i];
    return Polynomial(result_coeffs);
}

// Multiplication of two polynomials
Polynomial Polynomial::operator*(const Polynomial& other) const {
    int degree1 = this->coeffs.size();
    int degree2 = other.coeffs.size();

    // Resultant polynomial will have degree (degree1 + degree2 - 2)
    std::vector<double> result(degree1 + degree2 - 1, 0);

    // Perform multiplication
    for (int i = 0; i < degree1; i++) {
        for (int j = 0; j < degree2; j++) {
            result[i + j] += this->coeffs[i] * other.coeffs[j];
        }
    }

    return Polynomial(result);
}

// Equality operator
bool Polynomial::operator==(const Polynomial& other) const {
    return this->coeffs == other.coeffs;
}

// Output operator (friend function)
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            if (i != poly.coeffs.size() - 1 && poly.coeffs[i] > 0) out << "+";
            out << poly.coeffs[i];
            if (i > 0) out << "x^" << i << " ";
        }
    }
    return out;
}

// Utility functions
int Polynomial::degree() const {
    return coeffs.size() - 1;
}

double Polynomial::evaluate(double x) const {
    double result = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i)
        result = result * x + coeffs[i];
    return result;
}

Polynomial Polynomial::derivative() const {
    if (coeffs.size() <= 1) return Polynomial({0});
    vector<double> derivative_coeffs(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i)
        derivative_coeffs[i - 1] = i * coeffs[i];
    return Polynomial(derivative_coeffs);
}

Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result({0}); // Initialize result as the zero polynomial
    Polynomial term({1});   // Initialize term as q^0 (i.e., 1)

    // Perform composition, iterating through each coefficient of the current polynomial
    for (double coeff : this->coeffs) {
        // Add the current term (coefficient * q^i) to the result
        result = result + term * Polynomial({coeff});
        // Update the term by multiplying it by q (this builds q^i for the next term)
        term = term * q;
    }

    return result;
}

Polynomial Polynomial::integral() const {
    vector<double> integralCoeffs(this->coeffs.size() + 1, 0);
    for (int i = 0; i < this->coeffs.size(); i++) {
        integralCoeffs[i + 1] = this->coeffs[i] / (i + 1);
    }
    return Polynomial(integralCoeffs);
}

double Polynomial::integral(double x1, double x2) const {
    Polynomial integralPoly = this->integral();
    // Evaluate the indefinite integral at x2 and x1, then subtract
    return integralPoly.evaluate(x2) - integralPoly.evaluate(x1);
}

double Polynomial::getRoot(double guess, double tolerance, int maxIter) {
    double x = guess;

    for (int i = 0; i < maxIter; i++) {
        double fx = this->evaluate(x);       // p(x)
        double fpx = this->derivative().evaluate(x);  // p'(x)

        if (std::fabs(fx) < tolerance) {
            return x;  // Root found within tolerance
        }

        // Update x using Newton's method
        x = x - fx / fpx;
    }

    // If no root is found after maxIter, return the current guess
    return x;
}

// Set coefficients
void Polynomial::setCoefficients(const vector<double>& coefficients) {
    this->coeffs = coefficients;
}

// Get coefficient
double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size()) {
        throw out_of_range("Degree out of range");
    }
    return coeffs[degree];
}