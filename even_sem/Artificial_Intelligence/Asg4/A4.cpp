#include <math.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#define INF 1e9 + 7
#define delta 1e-5
using namespace std;

// minima at 1.54, 1.79
double f(double x, double y) {
    return 2 * x * x * x * x + y * y * y * y - x * x * y * y - x * x * x * y -
           2 * x * y * y;
}

// to accept random move
double prob(double steps) { 
    return pow(2, -(steps / 20));
}

void annealing(double x, double y, int steps) {
    cout << "\nX: " << x << "\nY: " << y << "\nValue: " << f(x, y)
         << "\nSteps: " << steps << "\n";

    if (steps > 500)
        return;

    double curr_val = f(x, y);
    double next_x = x + (rand() % 21 - 10) * 0.03;
    double next_y = y + (rand() % 21 - 10) * 0.03;

    if (f(next_x, next_y) <= curr_val) {
        annealing(next_x, next_y, ++steps);
    } else {
        if (prob(steps) >= 0.5) {
            annealing(next_x, next_y, ++steps);
        } else {
            annealing(x, y, ++steps);
        }
    }
}

int main() {
    freopen("output.txt", "w", stdout);
    cout << ios::fixed << setprecision(5);
    annealing(-10, -10, 0);
    return 0;
}
