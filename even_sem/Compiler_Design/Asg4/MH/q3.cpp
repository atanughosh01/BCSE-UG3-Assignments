#include <bits/stdc++.h>
#define int long long
#define MOD (int)1e9 + 7
using namespace std;

vector<string> split(string str, char del) {
    vector<string> ans;
    string temp = "";
    for (int i = 0; i < (int)str.size(); i++) {
        if (str[i] != del) {
            temp += str[i];
        }
        else {
            ans.push_back(temp);
            temp = "";
        }
    }
    ans.push_back(temp);
    return ans;
}

pair<string, string> removeLR(string start, string first, string beta) {
    string alpha = first.substr(1, first.size() - 1);
    pair<string, string> ans;
    ans.first = start + "->" + beta + start + "'";
    ans.second = start + "'->ep|" + alpha + start + "'";
    return ans;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("zin_3.txt", "r", stdin);
#endif
    // cout << "Enter the number of expressions:" << endl;
    int n;
    cin >> n;
    vector<string>arr(n);
    set<string>output;
    // cout << "Enter the expressions" << endl;
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = 0; i < n; i++) {
        string str = arr[i];
        if (str[0] == str[3]) {
            vector<string> exp = split(str, '|');
            int idx = -1;
            for (int j = 0; j < str.size(); j++) {
                if (str[j] == '|') {
                    idx = j;
                    break;
                }
            }
            exp[0] = str.substr(3, idx - 3);
            for (int j = 0; j <= exp.size() - 2; j++) {
                if (str[0] == exp[j][0]) {
                    string start;
                    start.push_back(str[0]);
                    pair<string, string> ans = removeLR(start, exp[j], exp[exp.size() - 1]);
                    output.insert(ans.first);
                    output.insert(ans.second);
                }
                else {
                    output.insert(str[0] + "->" + exp[j] + "|" + exp[exp.size() - 1]);
                }
            }
        }
        else {
            output.insert(str);
        }
    }
    cout << "Result: \n\n";
    for (auto ss : output)cout << ss << endl;
    return 0;
}


/*

5

s->abc
A->Aa|Ad|b
B->Bb|c
C->Cc|g

S->S*a|b

*/
