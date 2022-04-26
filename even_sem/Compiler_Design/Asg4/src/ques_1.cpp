#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

void printexp(string expr)
{
    int j = 0;
    cout << "Errors displayed with $" << endl
         << j << '\t';
    for (int i = 0; i < (expr.length() - 3); i++)
    {
        if (expr[i] == '#')
        {
            j++;
            cout << endl
                 << j << '\t';
            i++;
        }
        cout << expr[i];
    }
}

queue<int> areBracketsBalanced(string expr)
{
    stack<char> s;
    queue<int> q;
    char x;
    int line[100], linno = 1;
    for (int i = 0; i < expr.length(); i++)
    {
        int j = 0;
        if (expr[i] == '#')
        {
            linno++;
        }
        else if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
        {
            s.push(expr[i]);
            continue;
        }
        else if (expr[i] == ')')
        {
            x = s.top();
            if (x == '{' || x == '[' || x=='}' || x==']')
            {
                expr.insert((i + 1), "$");
                q.push(linno);
            }
            else
                s.pop();
        }
        else if (expr[i] == '}')
        {
            x = s.top();
            if (x == '(' || x == '[' || x==')' || x==']')
            {
                expr.insert((i + 1), "$");
                q.push(linno);
            }
            else
                s.pop();
        }
        else if (expr[i] == ']')
        {
            x = s.top();
            if (x == '(' || x == '{' || x==')' || x=='}')
            {
                expr.insert((i + 1), "$");
                q.push(linno);
            }
            else
                s.pop();
        }
        // else
        // {
        //     i++;
        // }
    }
//    printexp(expr);
    return q;
}

int main() {
    fstream f;
    string line, exp = "";
    f.open("code.txt");
    while (f)
    {
        getline(f, line);
        if (line == "-1")
            break;
        exp += line + '#';
    }
    // cout<<exp;
    queue<int> res = areBracketsBalanced(exp);
    while(res.size()) {
        cout << res.front() << "\n";
        res.pop();
    }
    return 0;
}



/*

int i = 0;
while (i<5) {
    int j=0;
    if(j%2==0) (
        printf("%d", &j);
    ]
    j++;
    i++;
}


while (i<5) {
    while (j<i) {
        int j=0;
        if(j%2==0) {
            int k = i+j;
        }
    }
]

*/
