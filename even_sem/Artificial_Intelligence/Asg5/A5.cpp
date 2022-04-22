#include <math.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <random>
#include <vector>
#define INF 1e9 + 7
using namespace std;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);

vector<int> fischer_yates(vector<int> &perm) {
    int n = (int)(perm.size());
    vector<int> ret = perm;
    for (int i = n; i >= 1; --i) {
        int idx = rand() % i;
        swap(ret[idx], ret[i - 1]);
    }
    return ret;
}

int score(vector<int> v) {
    int score = 0;
    int n = (int)(v.size());
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if (v[i] == v[j]) continue;
            if (j - i == v[j] - v[i]) continue;
            if (j - i == v[i] - v[j]) continue;
            score++;
        }
    return score;
}

int random_choice(vector<double> prob) {
    int n = (int)(prob.size());
    double rand_no = dis(gen);
    for (int i = 0; i < n; i++) {
        if (rand_no < prob[i]) {
            return i + 1;
        } else {
            rand_no -= prob[i];
        }
    }
    return -1;
}

pair<vector<int>, vector<int>> combine(vector<int> &v1, vector<int> &v2) {
    pair<vector<int>, vector<int>> ret;
    int n = (int)(v1.size());
    for (int i = 0; i < 3; i++) {
        ret.first.push_back(v1[i]);
        ret.second.push_back(v2[i]);
    }
    for (int i = 3; i < n; i++) {
        ret.first.push_back(v2[i]);
        ret.second.push_back(v1[i]);
    }
    return ret;
}

vector<int> mutation(vector<int> &v) {
    vector<int> ret = v;
    double prob = 0.05;
    int n = (int)(v.size());
    for (int i = 0; i < n; i++)
        if (double(dis(gen)) <= prob) {
            int choice = rand() % 8 + 1;
            ret[i] = choice;
        }
    return ret;
}

int main() {
    freopen("output.txt", "w", stdout);
    vector<int> perm = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = 32;
    vector<int> members[n + 1];
    for (int i = 1; i <= n; i++) {
        members[i] = fischer_yates(perm);
    }

    for (int itr = 1; itr <= 1000; itr++) {
        vector<int> scores;
        int sum = 0;
        bool done = false;
        cout << "MEMBER SCORES : (" << itr << ")" << endl;
        for (int i = 1; i <= n; i++) {
            int curr = score(members[i]);
            cout << curr;
            if (curr == 28) {
                done = true;
                cout << " HERE ";
                for (int x : members[i]) cout << x << " ";
                cout << endl;
            } else {
                cout << endl;
            }
            scores.push_back(curr);
            sum += curr;
        }

        if (done) break;
        vector<double> prob;
        for (auto x : scores) {
            prob.push_back(double(x) / double(sum));
        }

        int i1 = -1;
        int i2 = -1;
        int last = 1;
        vector<int> n_members[n + 1];

        for (int i = 1; i <= n / 2; i++) {
            while (true) {
                int curr = random_choice(prob);
                if (i1 == -1)
                    i1 = curr;
                else if (i2 == -1) {
                    if (i1 != curr) {
                        i2 = curr;
                        break;
                    }
                }
            }
            auto children = combine(members[i1], members[i2]);
            n_members[last] = children.first;
            n_members[last + 1] = children.second;
            last += 2;
            i1 = -1;
            i2 = -1;
        }
        for (int i = 1; i <= n; i++) {
            n_members[i] = mutation(n_members[i]);
        }
        for (int i = 1; i <= n; i++) {
            members[i] = n_members[i];
        }
    }
    return 0;
}
