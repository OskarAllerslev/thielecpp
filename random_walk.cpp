#include <iostream>
#include <vector>
#include <random>
#include <fstream>  // 🔹 Til at gemme data i en fil
#include <cmath>

using namespace std;

// Simulér en simpel random walk og gem hele kursudviklingen
vector<vector<double>> randomwalk(double S0, int steps, int simulations) {
    vector<vector<double>> all_simulations(simulations, vector<double>(steps + 1));

    random_device rd;
    mt19937 gen(rd());
    // uniform_int_distribution<> dist(-1, 1);  // 🔹 Tilfældige trin på -1 eller +1
    // student_t_distribution<> dist(1); // 🔹 Student-t-fordeling med 1 frihedsgrad
    normal_distribution<> dist(0.0, 0.5);  // 🔹 Standard normalfordeling

    for (int i = 0; i < simulations; i++) {
        double S = S0;
        all_simulations[i][0] = S;  // Startpris
        for (int j = 1; j <= steps; j++) {
            double epsilon = dist(gen);
            S += epsilon;
            all_simulations[i][j] = S;
        }
    }
    return all_simulations;
}

int main() {
    double S0 = 100; // Startpris
    int steps = 252; // Antal trin
    int simulations = 100; // 🔹 Antal simuleringer (ændr til flere hvis ønsket)

    vector<vector<double>> results = randomwalk(S0, steps, simulations);

    // 🔹 Gem data i en CSV-fil til plotting
    ofstream file("random_walk.csv");
    if (file.is_open()) {
        for (int j = 0; j <= steps; j++) {  // 🔹 Iterer over tidstrin
            for (int i = 0; i < simulations; i++) {
                file << results[i][j];  // 🔹 Skriver matrixdata til filen
                if (i < simulations - 1) file << ","; // Tilføj komma mellem kolonner
            }
            file << "\n";  // Nyt tidssteg (ny række)
        }
        file.close();
        cout << "Data gemt i 'random_walk.csv'!\n";
    } else {
        cout << "Kunne ikke åbne filen!\n";
    }

    return 0;
}
