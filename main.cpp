#include <iostream>
#include "include/Eigen/Dense"

using namespace Eigen;
using namespace std;

//compute P(s,t) using a discrete approximation

MatrixXd computeTransitionMatrix(const MatrixXd& Lambda, double dt, int steps){
    Eigen::MatrixXd P = MatrixXd::Identity(Lambda.rows(), Lambda.cols());

    for (int i = 0; i < steps; i++){
        P *= (MatrixXd::Identity(Lambda.rows(), Lambda.cols()) + Lambda*dt);

    }
    return P;
}

// Compute the reserve function V(t,T,r)
MatrixXd computeReserve(const MatrixXd& Lambda, const MatrixXd& R, double r, double t, double T, double dt){
    int steps = static_cast<int>((T-t) / dt);
    MatrixXd V = MatrixXd::Zero(R.rows(), R.cols());

    for (int i = 0; i < steps; i++){
        double u = t + i * dt;
        double discountFactor = exp(-r * (u-t));

        MatrixXd P_t_u = computeTransitionMatrix(Lambda, dt, i);
        MatrixXd P_u_T = computeTransitionMatrix(Lambda, dt, steps-i);

        V += discountFactor * P_t_u * R * P_u_T * dt;
    }
    return V;
}





int main() {
    // Define intensity matrix Lambda
    MatrixXd Lambda(2,2);
    Lambda << -0.02,  0.02,
               0.01, -0.01;

    // Define reward matrix R
    MatrixXd R(2,2);
    R << 100,  50,
          30, 200;

    double dt = 0.1;
    double t = 0.0;
    double T = 35;
    double r = 0.03;

    // Compute transition matrix P(s,t)
    MatrixXd P = computeTransitionMatrix(Lambda, dt, 10);
    cout << "Transition Matrix P(s,t):\n" << P << endl;

    // Compute reserve matrix V(t,T,r)
    MatrixXd V = computeReserve(Lambda, R, r, t, T, dt);
    cout << "Reserve Matrix V(t,T,r):\n" << V << endl;

    return 0;
}