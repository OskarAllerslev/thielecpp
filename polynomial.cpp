#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

class Polynomial {
public:
    std::vector<double> coefficients;

    Polynomial(std::vector<double> coeffs) : coefficients(coeffs){}

    double evaluate(double x) {
        double result = 0.0;
        int n = coefficients.size();
        for (int i = 0; i < n; i++){
            result += coefficients[i] * pow(x, n-1 - i );
        }
        return result;
    }

    Polynomial derivative() {
        std::vector<double> derivCoeffs;
        int n = coefficients.size();
        for (int i = 0; i < n -1; i++){
            derivCoeffs.push_back(coefficients[i] * (n-1-i));
        }
        return Polynomial(derivCoeffs);
    }

};


double newtonsMethod(Polynomial f, double x0, int maxIter = 1000, double tol = 1e-7) {
    Polynomial f_prime = f.derivative();
    double x = x0;

    for (int i = 0; i < maxIter; i++){
        double fx = f.evaluate(x);
        double fpx = f_prime.evaluate(x);

        if ( std::abs(fpx) < tol) break;

        double x_new = x - fx / fpx;
        if (std::abs(x_new - x) < tol ) return x_new;
        x = x_new;
    }
    return x;
}