#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#define INF 1e9 + 7

using namespace std;

struct answer {
    vector<int> order;
    vector<int> path;
};

int stack_state = 0;

answer bfs(int start, vector<int> goals, vector<vector<int>> adj) {
    queue<int> q;
    q.push(start);

    int n = int(adj.size());
    vector<bool> isgoal(n + 1, false);
    vector<int> parent(n + 1, -1);
    vector<bool> visited(n + 1, false);
    for (int x : goals) isgoal[x] = true;

    visited[start] = true;
    int last = -1;

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

    if (curr != -1)
        while (curr != -1) {
            ret.path.push_back(curr);
            curr = parent[curr];
        }

    reverse(ret.path.begin(), ret.path.end());
    return ret;
}

void dls_helper(int v, vector<bool> &isgoal, vector<vector<int>> &adj, int max_depth, 
                vector<bool> &marked, vector<int> &d, vector<int> &p, answer &ret) {
    for (auto u : adj[v])
        if (!marked[u] && d[v] < max_depth) {
            if (stack_state == 1)
                return;
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

void ibs_helper(int v, vector<bool> &isgoal, vector<vector<int>> &adj, int max_breadth, 
                vector<bool> &marked, vector<int> &br, vector<int> &p, answer &ret) {
    for (auto u : adj[v])
        if (!marked[u] && br[v] < max_breadth) {
            br[v] += 1;
            if (stack_state == 1)
                return;
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

answer dls(int start, vector<int> &goals, vector<vector<int>> &adj, int max_depth = INF) {
    int n = int(adj.size());
    vector<int> p(n + 1, -1);
    vector<bool> marked(n + 1, false);
    vector<int> d(n + 1, 0);
    vector<bool> isgoal(n + 1, false);
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
            if (curr == -1)
                break;
            else
                path.push_back(curr);
        }

        reverse(path.begin(), path.end());
        ret.path = path;
    }

    return ret;
}

answer ibs_ref(int start, vector<int> &goals, vector<vector<int>> &adj, int max_breadth) {
    int n = int(adj.size());
    vector<int> p(n + 1, -1);
    vector<bool> marked(n + 1, false);
    vector<int> br(n + 1, 0);
    vector<bool> isgoal(n + 1, false);
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
            if (curr == -1)
                break;
            else
                path.push_back(curr);
        }

        reverse(path.begin(), path.end());
        ret.path = path;
    }

    return ret;
}

answer ibs(int start, vector<int> goals, vector<vector<int>> adj) {
    int n = int(adj.size());
    for (int i = 0; i < n; i++) {
        answer a = ibs_ref(start, goals, adj, i);
        if (!a.path.empty()) return a;
    }
    answer foo;
    return foo;
}

answer ids(int start, vector<int> goals, vector<vector<int>> adj) {
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
    // freopen("output.txt", "r", stdout);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj;

    for (int i = 1; i <= n + 1; i++) {
        vector<int> x;
        adj.push_back(x);
    }

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    int start;
    cin >> start;
    vector<int> goal;
    int s;
    cin >> s;
    for (int i = 1; i <= s; i++) {
        int x;
        cin >> x;
        goal.push_back(x);
    }
    answer out = ibs(start, goal, adj);
    cout << "Order : ";
    for (auto x : out.order) cout << x << " ";
    cout << endl << "Path : " ;
    for (auto x : out.path) cout << x << " ";
    cout << endl;
    return 0;
}
