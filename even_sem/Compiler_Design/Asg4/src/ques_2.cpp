#include <bits/stdc++.h>
using namespace std;
int l = 0;
int fl = 0;

// E->iE'
// E'->+iE'|ep
// i+i$=>success

void match(string exp, char c) {
    if (exp[l] == c)
        l++;
    else {
        fl = 1;
        return;
    }
}

void Ed(string exp) {
    if (exp[l] == '+') {
        match(exp, '+');
        match(exp, 'i');
        Ed(exp);
    }
    else {
        return;
    }
}

void E(string exp)
{
    if (exp[l] == 'i') {
        match(exp, 'i');
        Ed(exp);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("zin.txt", "r", stdin);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        l = 0;
        fl = 0;
        string exp;
        cin >> exp;
        E(exp);
        if (exp[l] == '$' && fl == 0) {
            cout << "Parsing is Successful";
        } else {
            cout << "Parsing Failed";
        }
        cout << "\n";
    }
    return 0;
}
