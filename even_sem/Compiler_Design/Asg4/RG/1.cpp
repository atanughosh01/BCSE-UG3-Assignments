#include<iostream>
#include<stack>
using namespace std;
char matches[127];

int main(){
	stack<char> s;
	int line = 1;
	matches[')'] = '(';
	matches['}'] = '{';
	matches[']'] = '[';

	FILE *f = fopen("test.c","r");
	int c = fgetc(f);
	bool inquote = false;

	while(c!=EOF){
		//cout<<(char)c<<endl;
		if(c=='\n')
			line++;
		else if(c=='"' || c=='\'')
			inquote = !inquote;
		else if(!inquote){
			if(c=='(' || c=='{' || c=='[')
				s.push(c);
			else if(c==')' || c=='}' || c==']'){
				char top = s.top();
				if(top==matches[c])
					s.pop();
				else{
					cout<<"Wrong closing bracket in line "<<line<<endl;
					return 1;
				}
			}
		}

		c = fgetc(f);
	}

	if(!s.empty()){
		cout<<"Unmatched bracket found in line "<<(line)<<endl;
		return 1;
	}

	return 0;
}
