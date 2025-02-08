

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

// simuler aktikurser med GBM
vector<double> monteCarloGBM(double S0, double mu, double sigma, double T, int steps, int simulations){
    double dt = T / steps;
    vector<double> results(simulations);
    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister 19937 generator
    normal_distribution<> dist(0.0, 1.0); //standard normal distribution

    for (int i =0; i < simulations; i++){
        double S = S0;
        for (int j = 0; j < steps; j++){
            double Z = dist(gen);
            S *= exp((mu- 0.5 *sigma*sigma)*dt + sigma*sqrt(dt)* Z);
        }
        results[i] = S;
    }
    return results;
}

int main(){
    double S0 = 100;
    double mu = 0.05;
    double sigma = 0.2;
    double T = 1;
    int steps = 252;
    int simulations = 100000;

    vector<double> results = monteCarloGBM(S0, mu, sigma, T, steps, simulations);

    // udskriv de første 10 simulations

    std::cout << "Monte Carlo Simulation - Sidste pris på aktien: \n"; 
    for (int i = 0; i < 10; i++){
        std::cout << "Simulation " << i+1 << ": " << results[i] << std::endl;
    }
    return 0;
}