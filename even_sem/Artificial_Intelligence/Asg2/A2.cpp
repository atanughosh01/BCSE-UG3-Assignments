#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>
#define INF 1e9 + 7

using namespace std;

struct answer {
    vector<int> order;
    vector<int> path;
};

answer best_first_search(int s, int e, vector<pair<int, int>> adj[], int h[], int n) {
    int p[n + 1];
    for (int i = 1; i <= n; i++) p[i] = -1;

    answer ret;

    vector<bool> marked(n + 1, false);
    set<pair<int, int>> st;  // dist, vertex
    st.insert({h[s], s});

    marked[s] = true;

    while (true) {
        auto v = *st.begin();
        ret.order.push_back(v.second);

        st.erase(v);

        if (v.second == e) break;

        for (auto u : adj[v.second])
            if (!marked[u.first]) {
                st.insert({h[u.first], u.first});
                p[u.first] = v.second;
                marked[u.first] = true;
            }
    }

    int curr = e;
    while (curr != -1) {
        ret.path.push_back(curr);
        curr = p[curr];
    }

    reverse(ret.path.begin(), ret.path.end());

    return ret;
}

answer astar(int s, int e, vector<pair<int, int>> adj[], int h[], int n) {
    set<pair<int, int>> st;
    vector<int> d(n + 1, INF);
    vector<int> p(n + 1, -1);
    d[s] = h[s];

    answer ret;
    st.insert({h[s], s});

    while (true) {
        auto v = *st.begin();
        ret.order.push_back(v.second);

        st.erase(v);

        if (v.second == e) break;

        for (auto u : adj[v.second])
            if (d[u.first] >
                d[v.second] - h[v.second] + h[u.first] + u.second) {
                st.erase({d[u.first], u.first});
                d[u.first] = d[v.second] - h[v.second] + h[u.first] + u.second;
                st.insert({d[u.first], u.first});
                p[u.first] = v.second;
            }
    }

    int curr = e;
    while (curr != -1) {
        ret.path.push_back(curr);
        curr = p[curr];
    }

    reverse(ret.path.begin(), ret.path.end());

    return ret;
}

int main() {
    // freopen("input.txt", "r", stdin);
    cout << "Enter n and m -->\n";
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> adj[n + 1];
    int h[n + 1];

    cout << "Enter Graph -->\n";
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    cout << "Enter s and e -->\n";
    int s, e;
    cin >> s >> e;
    cout << "Enter " << n << " values (Elements of array h) -->\n";
    for (int i = 1; i <= n; i++) cin >> h[i];

    answer out;
    cout << "1.Best First Search\n2. A Star Search\nEnter --> ";
    int ch;
    cin >> ch;
    if (ch == 1){
        out = best_first_search(s, e, adj, h, n);
    } else if (ch==2) {
        out = astar(s, e, adj, h, n);
    } else {
        cout << "Invalid Input\n";
        exit(0);
    }

    cout << "Order : ";
    for (auto x : out.order) cout << x << " ";
    cout << endl << "Path : ";
    for (auto x : out.path) cout << x << " ";
    cout << endl;
    return 0;
}
