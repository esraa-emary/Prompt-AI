#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <set> // For storing unique roots
using namespace std;

// Function to find all unique real roots
set<double> findAllRealRoots(Polynomial& poly, double startRange, double endRange, double stepSize, double tolerance = 1e-6, int maxIter = 100) {
    set<double> roots; // To store unique roots

    // Iterate through the range using the step size
    for (double x = startRange; x < endRange; x += stepSize) {
        // Check the value of the polynomial at x and x + stepSize
        double f_x = poly.evaluate(x);
        double f_x_next = poly.evaluate(x + stepSize);

        // If there is a sign change between f_x and f_x_next, there is a root in between
        if (f_x * f_x_next < 0) {
            // Perform a root-finding method (Newton's method or bisection) in this interval
            double root = poly.getRoot(x + stepSize / 2, tolerance, maxIter); // Start at the midpoint
            if (!isnan(root)) {
                roots.insert(root); // Add unique root
            }
        }
    }

    return roots; // Return all found roots
}

void displayMenu() {
    cout << "\nSelect an operation: \n";
    cout << "1. View p1\n";
    cout << "2. View p2\n";
    cout << "3. Add p1 and p2\n";
    cout << "4. Subtract p1 from p2\n";
    cout << "5. Multiply p1 and p2\n";
    cout << "6. Evaluate p1 at a point\n";
    cout << "7. Evaluate p2 at a point\n";
    cout << "8. Derivative of p1\n";
    cout << "9. Derivative of p2\n";
    cout << "10. Composition of p1 with p2\n";
    cout << "11. Composition of p2 with p1\n";
    cout << "12. Indefinite integral of p1\n";
    cout << "13. Indefinite integral of p2\n";
    cout << "14. Definite integral of p1 over an interval\n";
    cout << "15. Definite integral of p2 over an interval\n";
    cout << "16. Get coefficient of a specific degree for p1\n";
    cout << "17. Get coefficient of a specific degree for p2\n";
    cout << "18. Check if p1 equals p2\n";
    cout << "19. Find root of p1 using Newton's method\n";
    cout << "20. Find root of p2 using Newton's method\n";
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
                    cout << "p1: " << p1 << endl;
                    break;
                }
                case 2: {
                    cout << "p2: " << p2 << endl;
                    break;
                }
                case 3: {
                    Polynomial sum = p1 + p2;
                    cout << "p1 + p2: " << sum << endl;
                    break;
                }
                case 4: {
                    Polynomial difference = p1 - p2;
                    cout << "p1 - p2: " << difference << endl;
                    break;
                }
                case 5: {
                    Polynomial product = p1 * p2;
                    cout << "p1 * p2: " << product << endl;
                    break;
                }
                case 6: {
                    cout << "Enter value of x to evaluate p1: ";
                    cin >> x;
                    cout << "p1 evaluated at x = " << x << ": " << p1.evaluate(x) << endl;
                    break;
                }
                case 7: {
                    cout << "Enter value of x to evaluate p2: ";
                    cin >> x;
                    cout << "p2 evaluated at x = " << x << ": " << p2.evaluate(x) << endl;
                    break;
                }
                case 8: {
                    Polynomial p1_derivative = p1.derivative();
                    cout << "Derivative of p1: " << p1_derivative << endl;
                    break;
                }
                case 9: {
                    Polynomial p2_derivative = p2.derivative();
                    cout << "Derivative of p2: " << p2_derivative << endl;
                    break;
                }
                case 10: {
                    Polynomial composition = p1.compose(p2);
                    cout << "Composition of p1 with p2: " << composition << endl;
                    break;
                }
                case 11: {
                    Polynomial composition2 = p2.compose(p1);
                    cout << "Composition of p2 with p1: " << composition2 << endl;
                    break;
                }
                case 12: {
                    Polynomial p1_integral = p1.integral();
                    cout << "Indefinite integral of p1: " << p1_integral << endl;
                    break;
                }
                case 13: {
                    Polynomial p2_integral = p2.integral();
                    cout << "Indefinite integral of p2: " << p2_integral << endl;
                    break;
                }
                case 14: {
                    cout << "Enter lower and upper bounds for definite integral of p1: ";
                    cin >> x1 >> x2;
                    cout << "Definite integral of p1 from " << x1 << " to " << x2 << ": " << p1.integral(x1, x2) << endl;
                    break;
                }
                case 15: {
                    cout << "Enter lower and upper bounds for definite integral of p2: ";
                    cin >> x1 >> x2;
                    cout << "Definite integral of p2 from " << x1 << " to " << x2 << ": " << p2.integral(x1, x2) << endl;
                    break;
                }
                case 16: {
                    cout << "Enter degree to get coefficient of p1: ";
                    cin >> degree;
                    try {
                        cout << "Coefficient of x^" << degree << " in p1: " << p1.getCoefficient(degree) << endl;
                    } catch (const out_of_range& e) {
                        cout << e.what() << endl;
                    }
                    break;
                }
                case 17: {
                    cout << "Enter degree to get coefficient of p2: ";
                    cin >> degree;
                    try {
                        cout << "Coefficient of x^" << degree << " in p2: " << p2.getCoefficient(degree) << endl;
                    } catch (const out_of_range& e) {
                        cout << e.what() << endl;
                    }
                    break;
                }
                case 18: {
                    cout << "p1 is equal to p2: " << (p1 == p2 ? "True" : "False") << endl;
                    break;
                }
                case 19: {
                    set<double> roots = findAllRealRoots(p1, -10, 10, 0.1);
                    cout << "Real roots of Polynomial 1: [";
                    if (roots.empty()) {
                        cout << "]" << endl;
                    } else {
                        for (auto it = roots.begin(); it != roots.end();) {
                            cout << *it;
                            ++it;
                            if (it != roots.end()) {
                                cout << ", ";
                            }
                        }
                        cout << "]" << endl;
                    }
                    break;
                }
                case 20: {
                    set<double> roots = findAllRealRoots(p2, -10, 10, 0.1);
                    cout << "Real roots of Polynomial 2: [";
                    if (roots.empty()) {
                        cout << "]" << endl;
                    } else {
                        for (auto it = roots.begin(); it != roots.end();) {
                            cout << *it;
                            ++it;
                            if (it != roots.end()) {
                                cout << ", ";
                            }
                        }
                        cout << "]" << endl;
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
