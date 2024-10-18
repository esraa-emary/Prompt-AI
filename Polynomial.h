//
// Created by NAGHAM on 10/15/2024.
//

#ifndef OOP_ASSIGNMENT_1_POLYNOMIAL_H
#define OOP_ASSIGNMENT_1_POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Polynomial {
private:
    vector<double> coeffs; // Store coefficients of the polynomial

public:
    // Constructors
    Polynomial(); // Default constructor
    Polynomial(const vector<double>& coefficients); // Constructor with coefficients
    Polynomial(const Polynomial& other); // Copy constructor

    // Destructor
    ~Polynomial();

    // Assignment operator
    Polynomial& operator=(const Polynomial& other);

    // Arithmetic operators
    Polynomial operator+(const Polynomial& other) const; // Addition
    Polynomial operator-(const Polynomial& other) const; // Subtraction
    Polynomial operator*(const Polynomial& other) const; // Multiplication

    // Equality operator
    bool operator==(const Polynomial& other) const;

    // Output operator (friend function to access private members)
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

    // Utility functions
    int degree() const; // Return the degree of the polynomial
    double evaluate(double x) const; // Evaluate the polynomial at x
    Polynomial compose(const Polynomial& q) const; // Compose this polynomial with q
    Polynomial derivative() const; // Derivative of the polynomial
    Polynomial integral() const; // Return the indefinite integral of the polynomial
    double integral(double x1, double x2) const; // Definite integral from x1 to x2
    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100); // Newton's method to find a root

    // Getter and setter for coefficients
    void setCoefficients(const vector<double>& coefficients); // Set the coefficients
    double getCoefficient(int degree) const; // Get the coefficient of a specific degree
};

#endif // OOP_ASSIGNMENT_1_POLYNOMIAL_H