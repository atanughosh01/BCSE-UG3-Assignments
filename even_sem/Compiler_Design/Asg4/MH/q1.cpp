// #include <bits/stdc++.h>
// // #include <iostream>
// // #include <fstream>
// using namespace std;
// #define endl "\n"

// void printexp(string expr) {
// 	int j = 0;
// 	cout << "Errors displayed with $" << endl << j << '\t';
// 	for (int i = 0; i < (expr.length() - 3); i++) {
// 		if (expr[i] == '#') {
// 			j++;
// 			cout << endl << j << '\t';
// 			i++;
// 		}
// 		cout << expr[i];
// 	}
// }

// queue<int> areBracketsBalanced(string expr) {
// 	stack<char> s;
// 	queue<int> q;
// 	char x;
// 	int line[100], line_no = 1;
// 	for (int i = 0; i < expr.length(); i++)	{
// 		int j = 0;
// 		if (expr[i] == '#') {
// 			line_no++;
// 		}
// 		else if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
// 			s.push(expr[i]);
// 			continue;
// 		}
// 		else if (expr[i] == ')') {
// 			x = s.top();
// 			if (x == '{' || x == '[') {
// 				expr.insert((i + 1), "$");
// 				q.push(line_no);
// 			}
// 			else
// 				s.pop();
// 		}
// 		else if (expr[i] == '}') {
// 			x = s.top();
// 			if (x == '(' || x == '[') {
// 				expr.insert((i + 1), "$");
// 				q.push(line_no);
// 			}
// 			else
// 				s.pop();
// 		}
// 		else if (expr[i] == ']') {
// 			x = s.top();
// 			if (x == '(' || x == '{') {
// 				expr.insert((i + 1), "$");
// 				q.push(line_no);
// 			}
// 			else {
// 				s.pop();
// 			}
// 		}
// 		else {
// 			i++;
// 		}
// 	}
// 	printexp(expr);
// 	return q;
// }

// // Driver code
// int main() {
// 	fstream f;
// 	string line, exp = "";
// 	f.open("code.txt");
// 	while (f) {
// 		getline(f, line);
// 		if (line == "-1")
// 			break;
// 		exp += line + '#';
// 	}
// 	queue<int> res = areBracketsBalanced(exp);
// 	return 0;
// }





// CPP program to check for balanced brackets.
#include <bits/stdc++.h>
using namespace std;

// function to check if brackets are balanced
bool areBracketsBalanced(string expr)
{
	stack<char> s;
	char x;

	// Traversing the Expression
	for (int i = 0; i < expr.length(); i++)
	{
		if (expr[i] == '(' || expr[i] == '['
			|| expr[i] == '{')
		{
			// Push the element in the stack
			s.push(expr[i]);
			continue;
		}

		// IF current current character is not opening
		// bracket, then it must be closing. So stack
		// cannot be empty at this point.
		if (s.empty())
			return false;

		switch (expr[i]) {
		case ')':
			
			// Store the top element in a
			x = s.top();
			s.pop();
			if (x == '{' || x == '[')
				return false;
			break;

		case '}':

			// Store the top element in b
			x = s.top();
			s.pop();
			if (x == '(' || x == '[')
				return false;
			break;

		case ']':

			// Store the top element in c
			x = s.top();
			s.pop();
			if (x == '(' || x == '{')
				return false;
			break;
		}
	}

	// Check Empty Stack
	return (s.empty());
}

// // Driver code
// int main() {
// 	string expr = "{()}[]";
// 	// Function call
// 	if (areBracketsBalanced(expr))
// 		cout << "Balanced";
// 	else
// 		cout << "Not Balanced";
// 	return 0;
// }


// Driver code
int main() {
	fstream f;
	string line, exp = "";
	f.open("code.txt");
	while (f) {
		getline(f, line);
		if (line == "-1")
			break;
		exp += line + '#';
	}
	bool res = areBracketsBalanced(exp);
	return 0;
}
