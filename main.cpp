#include "Polynomial.h"
#include <iostream>
#include <vector>
using namespace std;

void displayMenu() {
    cout << "\nSelect an operation: \n";
    cout << "1. Add p1 and p2\n";
    cout << "2. Subtract p1 from p2\n";
    cout << "3. Multiply p1 and p2\n";
    cout << "4. Evaluate p1 at a point\n";
    cout << "5. Evaluate p2 at a point\n";
    cout << "6. Derivative of p1\n";
    cout << "7. Derivative of p2\n";
    cout << "8. Composition of p1 with p2\n";
    cout << "9. Composition of p2 with p1\n";
    cout << "10. Indefinite integral of p1\n";
    cout << "11. Indefinite integral of p2\n";
    cout << "12. Definite integral of p1 over an interval\n";
    cout << "13. Definite integral of p2 over an interval\n";
    cout << "14. Get coefficient of a specific degree for p1\n";
    cout << "15. Get coefficient of a specific degree for p2\n";
    cout << "16. Check if p1 equals p2\n";
    cout << "17. Find root of p1 using Newton's method\n";
    cout << "18. Find root of p2 using Newton's method\n";
    cout << "0. Exit\n";
}

int main() {
    int numTestCases;
    cout << "Enter number of test cases: ";
    cin >> numTestCases;

    for (int t = 0; t < numTestCases; ++t) {
        cout << "\nTest case " << t + 1 << ":\n";

        // Input the two polynomials
        vector<double> coeffs1, coeffs2;
        int degree1, degree2;

        cout << "Enter degree of first polynomial: ";
        cin >> degree1;
        coeffs1.resize(degree1 + 1);
        cout << "Enter coefficients of p1 from constant term to highest degree: ";
        for (int i = 0; i <= degree1; ++i) {
            cin >> coeffs1[i];
        }

        cout << "Enter degree of second polynomial: ";
        cin >> degree2;
        coeffs2.resize(degree2 + 1);
        cout << "Enter coefficients of p2 from constant term to highest degree: ";
        for (int i = 0; i <= degree2; ++i) {
            cin >> coeffs2[i];
        }

        Polynomial p1(coeffs1);
        Polynomial p2(coeffs2);

        while (true) {
            displayMenu();
            int choice;
            cout << "Choose an operation (0 to exit): ";
            cin >> choice;

            if (choice == 0) break;

            double x, x1, x2;
            int degree;

            switch (choice) {
                case 1: {
                    Polynomial sum = p1 + p2;
                    cout << "p1 + p2: " << sum << endl;
                    break;
                }
                case 2: {
                    Polynomial difference = p1 - p2;
                    cout << "p1 - p2: " << difference << endl;
                    break;
                }
                case 3: {
                    Polynomial product = p1 * p2;
                    cout << "p1 * p2: " << product << endl;
                    break;
                }
                case 4: {
                    cout << "Enter value of x to evaluate p1: ";
                    cin >> x;
                    cout << "p1 evaluated at x = " << x << ": " << p1.evaluate(x) << endl;
                    break;
                }
                case 5: {
                    cout << "Enter value of x to evaluate p2: ";
                    cin >> x;
                    cout << "p2 evaluated at x = " << x << ": " << p2.evaluate(x) << endl;
                    break;
                }
                case 6: {
                    Polynomial p1_derivative = p1.derivative();
                    cout << "Derivative of p1: " << p1_derivative << endl;
                    break;
                }
                case 7: {
                    Polynomial p2_derivative = p2.derivative();
                    cout << "Derivative of p2: " << p2_derivative << endl;
                    break;
                }
                case 8: {
                    Polynomial composition = p1.compose(p2);
                    cout << "Composition of p1 with p2: " << composition << endl;
                    break;
                }
                case 9: {
                    Polynomial composition2 = p2.compose(p1);
                    cout << "Composition of p2 with p1: " << composition2 << endl;
                    break;
                }
                case 10: {
                    Polynomial p1_integral = p1.integral();
                    cout << "Indefinite integral of p1: " << p1_integral << endl;
                    break;
                }
                case 11: {
                    Polynomial p2_integral = p2.integral();
                    cout << "Indefinite integral of p2: " << p2_integral << endl;
                    break;
                }
                case 12: {
                    cout << "Enter lower and upper bounds for definite integral of p1: ";
                    cin >> x1 >> x2;
                    cout << "Definite integral of p1 from " << x1 << " to " << x2 << ": " << p1.integral(x1, x2) << endl;
                    break;
                }
                case 13: {
                    cout << "Enter lower and upper bounds for definite integral of p2: ";
                    cin >> x1 >> x2;
                    cout << "Definite integral of p2 from " << x1 << " to " << x2 << ": " << p2.integral(x1, x2) << endl;
                    break;
                }
                case 14: {
                    cout << "Enter degree to get coefficient of p1: ";
                    cin >> degree;
                    try {
                        cout << "Coefficient of x^" << degree << " in p1: " << p1.getCoefficient(degree) << endl;
                    } catch (const out_of_range& e) {
                        cout << e.what() << endl;
                    }
                    break;
                }
                case 15: {
                    cout << "Enter degree to get coefficient of p2: ";
                    cin >> degree;
                    try {
                        cout << "Coefficient of x^" << degree << " in p2: " << p2.getCoefficient(degree) << endl;
                    } catch (const out_of_range& e) {
                        cout << e.what() << endl;
                    }
                    break;
                }
                case 16: {
                    cout << "p1 is equal to p2: " << (p1 == p2 ? "True" : "False") << endl;
                    break;
                }
                case 17: {
                    cout << "Enter initial guess for Newton's method to find root of p1: ";
                    cin >> x;
                    try {
                        double root = p1.getRoot(x);
                        cout << "Root of p1: " << root << endl;
                    } catch (const runtime_error& e) {
                        cout << e.what() << endl;
                    }
                    break;
                }
                case 18: {
                    cout << "Enter initial guess for Newton's method to find root of p2: ";
                    cin >> x;
                    try {
                        double root = p2.getRoot(x);
                        cout << "Root of p2: " << root << endl;
                    } catch (const runtime_error& e) {
                        cout << e.what() << endl;
                    }
                    break;
                }
                default:
                    cout << "Invalid choice, please try again.\n";
            }
        }
    }

    return 0;
}
