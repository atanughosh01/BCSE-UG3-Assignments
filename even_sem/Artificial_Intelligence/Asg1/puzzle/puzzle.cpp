#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#define INF 1e9 + 7
using namespace std;

struct answer {
    vector<int> order;
    vector<int> path;
};

int stack_state = 0;

int to_id(vector<int> v) {
    int mul = 1;
    reverse(v.begin(), v.end());
    int ans = 0;
    for (int x : v) {
        ans = ans + x * mul;
        mul *= 9;
    }
    return ans;
}

void print_state(int v) {
    vector<int> state;
    for (int i = 0; i < 9; i++) {
        state.push_back(v % 9);
        v = v / 9;
    }
    reverse(state.begin(), state.end());
    cout << state[0] << " " << state[1] << " " << state[2] << endl
         << state[3] << " " << state[4] << " " << state[5] << endl
         << state[6] << " " << state[7] << " " << state[8] << endl;
}

answer bfs(int start, vector<int> &goals, map<int, vector<int>> &adj) {
    queue<int> q;
    q.push(start);

    map<int, bool> isgoal;
    map<int, int> parent;
    map<int, bool> visited;
    for (int x : goals) isgoal[x] = true;

    visited[start] = true;
    int last = 0;

    answer ret;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ret.order.push_back(v);

        if (isgoal[v]) {
            last = v;
            break;
        }

        for (auto u : adj[v])
            if (!visited[u]) {
                q.push(u);
                visited[u] = true;
                parent[u] = v;
            }
    }

    int curr = last;

    if (curr != 0)
        while (curr != 0) {
            ret.path.push_back(curr);
            curr = parent[curr];
        }

    reverse(ret.path.begin(), ret.path.end());
    return ret;
}

void dls_helper(int v, map<int, bool> &isgoal, map<int, vector<int>> &adj,
                int max_depth, map<int, bool> &marked, map<int, int> &d,
                map<int, int> &p, answer &ret) {
    for (auto u : adj[v])
        if (!marked[u] && d[v] < max_depth) {
            if (stack_state == 1) return;

            ret.order.push_back(u);
            marked[u] = true;
            d[u] = 1 + d[v];
            p[u] = v;

            if (isgoal[u]) {
                stack_state = 1;
                ret.path.push_back(u);
                return;
            } else {
                dls_helper(u, isgoal, adj, max_depth, marked, d, p, ret);
            }
        }
}

void ibs_helper(int v, map<int, bool> &isgoal, map<int, vector<int>> &adj,
                int max_breadth, map<int, bool> &marked, map<int, int> &br,
                map<int, int> &p, answer &ret) {
    for (auto u : adj[v])
        if (!marked[u] && br[v] < max_breadth) {
            br[v] += 1;
            if (stack_state == 1) return;

            ret.order.push_back(u);
            marked[u] = true;
            p[u] = v;

            if (isgoal[u]) {
                stack_state = 1;
                ret.path.push_back(u);
                return;
            } else {
                ibs_helper(u, isgoal, adj, max_breadth, marked, br, p, ret);
            }
        }
}

answer dls(int start, vector<int> &goals, map<int, vector<int>> &adj, int max_depth = INF) {
    map<int, int> p;
    map<int, bool> marked;
    map<int, int> d;
    map<int, bool> isgoal;
    answer ret;
    stack_state = 0;
    for (auto u : goals) isgoal[u] = true;

    marked[start] = true;
    ret.order.push_back(start);
    dls_helper(start, isgoal, adj, max_depth, marked, d, p, ret);

    if (!ret.path.empty()) {
        vector<int> path;
        int curr = *ret.path.rbegin();
        ret.path.pop_back();
        path.push_back(curr);

        while (true) {
            curr = p[curr];
            if (curr == 0)
                break;
            else
                path.push_back(curr);
        }

        reverse(path.begin(), path.end());
        ret.path = path;
    }

    return ret;
}

answer ibs_ref(int start, vector<int> &goals, map<int, vector<int>> &adj, int max_breadth) {
    map<int, int> p;
    map<int, bool> marked;
    map<int, int> br;
    map<int, bool> isgoal;
    answer ret;
    stack_state = 0;
    for (auto u : goals) isgoal[u] = true;

    marked[start] = true;
    ret.order.push_back(start);
    ibs_helper(start, isgoal, adj, max_breadth, marked, br, p, ret);

    if (!ret.path.empty()) {
        vector<int> path;
        int curr = *ret.path.rbegin();
        ret.path.pop_back();
        path.push_back(curr);

        while (true) {
            curr = p[curr];
            if (curr == 0)
                break;
            else
                path.push_back(curr);
        }

        reverse(path.begin(), path.end());
        ret.path = path;
    }

    return ret;
}

answer ibs(int start, vector<int> goals, map<int, vector<int>> &adj) {
    int n = int(adj.size());
    for (int i = 0; i < n; i++) {
        answer a = ibs_ref(start, goals, adj, i);
        if (!a.path.empty()) return a;
    }

    answer foo;
    return foo;
}

answer ids(int start, vector<int> goals, map<int, vector<int>> &adj) {
    int n = int(adj.size());
    for (int i = 0; i < n; i++) {
        answer a = dls(start, goals, adj, i);
        if (!a.path.empty()) return a;
    }

    answer foo;
    return foo;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    map<int, vector<int>> adj;

    vector<int> perm = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    do {
        int idx = -1;
        for (int i = 0; i < 9; i++) {
            if (perm[i] == 0)
                idx = i;
        }

        vector<int> next;

        if (idx % 3 != 2) {
            next = perm;
            swap(next[idx], next[idx + 1]);
            adj[to_id(perm)].push_back(to_id(next));
        }
        if (idx % 3 != 0) {
            next = perm;
            swap(next[idx], next[idx - 1]);
            adj[to_id(perm)].push_back(to_id(next));
        }
        if (idx / 3 != 2) {
            next = perm;
            swap(next[idx], next[idx + 3]);
            adj[to_id(perm)].push_back(to_id(next));
        }
        if (idx / 3 != 0) {
            next = perm;
            swap(next[idx], next[idx - 3]);
            adj[to_id(perm)].push_back(to_id(next));
        }

    } while (next_permutation(perm.begin(), perm.end()));

    vector<int> start_state;
    for (int i = 0; i < 9; i++) {
        int x;
        cin >> x;
        start_state.push_back(x);
    }

    int start = to_id(start_state);

    vector<int> goal_state = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    int goal = to_id(goal_state);

    vector<int> goals;
    goals.push_back(goal);

    answer out = ibs(start, goals, adj);

    cout << "ORDER (" << (int)(out.order.size()) << " steps)" << endl;
    for (auto x : out.order) print_state(x), cout << endl;
    cout << endl
         << "PATH (" << (int)(out.path.size()) << " steps)" << endl
         << endl;
    for (auto x : out.path) print_state(x), cout << endl;

    return 0;
}
