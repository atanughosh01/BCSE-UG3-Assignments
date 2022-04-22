/**
 * 
 *  An Implementation of Solution to the Classic
 *  8-Puzzle Problem using 'Hill-Climbing' Algorithm
 * 
 *  This is a NON-Optimal Solution
 * 
 */

#include<iostream>
#include<vector>
#define endl "\n"
#define debug(x) cerr << #x << ": " << x << endl;
using namespace std;

vector<vector<int>> start(3, vector<int> (3));
vector<vector<int>> final(3, vector<int> (3));

void read() {
    cout.precision(15); cout << fixed;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    #ifndef LOCAL
        freopen("input.txt", "r", stdin);
        // freopen("output.txt", "w", stdout);
    #endif
}

void input(vector<vector<int>>& arr, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
}

void output(vector<vector<int>>& arr, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

bool isArrayMatched (vector<vector<int>> &start, vector<vector<int>>& final) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (start[i][j] != final[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int manhattanDist(vector<vector<int>> &temp, vector<vector<int>> &final) {
    int d = 0;
    for (int xi = 0; xi < 3; xi++) {
        for (int yi = 0; yi < 3; yi++) {
            for (int xj = 0; xj < 3; xj++) {
                for (int yj = 0; yj < 3; yj++) {
                    if (temp[xi][yi] == final[xj][yj]) {
                        d += (abs(xi - xj) + abs(yi - yj));
                    }
                }
            }
        }
    }
    return d;
}

int main () {
    read();

    cout << "\nEnter initial state : \n";
    input(start, 3, 3);
    output(start, 3, 3);

    cout << "\nEnter final state : \n";
    input(final, 3, 3);
    output(final, 3, 3);

    cout << "\nSolution of the puzzle is as follows- \nInitial State: 0\n";
    output(start, 3, 3);

    vector<vector<int>> temp = start;
    int n = 0;
    while (!isArrayMatched(start, final)) {
        vector<int> mh_dist(4, INT_MAX);
        int x = -1, y = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (temp[i][j] == 0) {
                    x = i;
                    y = j;
                }
            }
        }

        if (y - 1 >= 0) {
            swap(temp[x][y - 1], temp[x][y]);
            mh_dist[0] = manhattanDist(temp, final);
            swap(temp[x][y - 1], temp[x][y]);
        }
        if (y + 1 <= 2) {
            swap(temp[x][y + 1], temp[x][y]);
            mh_dist[1] = manhattanDist(temp, final);
            swap(temp[x][y + 1], temp[x][y]);
        }
        if (x - 1 >= 0) {
            swap(temp[x - 1][y], temp[x][y]);
            mh_dist[2] = manhattanDist(temp, final);
            swap(temp[x - 1][y], temp[x][y]);
        }
        if (x + 1 <= 2) {
            swap(temp[x + 1][y], temp[x][y]);
            mh_dist[3] = manhattanDist(temp, final);
            swap(temp[x + 1][y], temp[x][y]);
        }

        int idx = -1, min_t = INT_MAX;
        for (int i = 0; i <= 3; i++) {
            if (mh_dist[i] < min_t) {
                min_t = mh_dist[i];
                idx = i;
            }
        }

        if (idx == 0) {
            swap(temp[x][y - 1], temp[x][y]);
        }
        if (idx == 1) {
            swap(temp[x][y + 1], temp[x][y]);
        }
        if (idx == 2) {
            swap(temp[x - 1][y], temp[x][y]);
        }
        if (idx == 3) {
            swap(temp[x + 1][y], temp[x][y]);
        }
        cout << endl;
        start = temp;
        cout << "State: " << ++n << endl;
        output(start, 3, 3);
    }
    cout << "\n-- Target State Found --\n";
    cout.flush();
    return 0;
}



/*
    ------- SAMPLE TESTCASE ------

Enter initial state :
2 8 3
1 6 4
7 0 5

Enter final state :
1 2 3
8 0 4
7 6 5

Solution of the puzzle :
2 8 3
1 6 4
7 0 5

2 8 3
1 0 4
7 6 5

2 0 3
1 8 4
7 6 5

0 2 3
1 8 4
7 6 5

1 2 3
0 8 4
7 6 5

1 2 3
8 0 4
7 6 5

-- Target State Found --

*/
