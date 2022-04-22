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

void hill_climbing(double x, double y, int steps) {
    cout << "\nX: " << x << "\nY: " << y << "\nValue: " << f(x, y)
         << "\nSteps: " << steps << "\n";

    double curr_val = f(x, y);

    bool found = false;
    double next_x, next_y;
    double best = curr_val;

    for (double i = -0.1; i <= 0.1; i += 0.01) {
        for (double j = -0.1; j <= 0.1; j += 0.01) {
            if (!(abs(i) <= delta && abs(j) <= delta)) {
                if (f(x + i, y + j) < best) {
                    found = true, next_x = x + i, next_y = y + j, best = f(x + i, y + j);
                }
            }
        }
    }

    if (!found)
        return;

    hill_climbing(next_x, next_y, ++steps);
}

int main() {
    freopen("output.txt", "w", stdout);
    cout << ios::fixed << setprecision(5);
    hill_climbing(-10, -10, 0);
    return 0;
}
