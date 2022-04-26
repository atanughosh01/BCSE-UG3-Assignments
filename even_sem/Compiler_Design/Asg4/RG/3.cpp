#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int main()
{
	int n, j, l, i, k;
	
	string d, a, b, flag;
	char c;
	cout<<"Enter Parent Non-Terminal(single capital letter): ";
	cin >> c;
	d.push_back(c);
	a += d + "\'->";
	d += "->";
	b += d;
	cout<<"Enter number of productions: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout<<"Enter Production ";
		cout<<i + 1<<" :";
		cin >> flag;
		d += flag;
		if (i != n - 1)
		{
			d += "|";	
		}
	}
	cout<<"The Production Rule is: ";
	cout<<d<<endl;

	for (i = 0, k = 3; i < n; i++)
	{
		if (d[0] != d[k])
		{
			cout<<"Production: "<< i + 1;
			cout<<" does not have left recursion.";
			cout<<endl;

			if(isupper(d[k])){
				while(k<d.size() && d[k] !='|')
					b.push_back(d[k++]);
			}else{
				b.push_back(d[k++]);
			}
			
			b.push_back(d[0]);
			b += "'";
			
			if(i!=n-1)
				b += "|";
		}
		else
		{
			cout<<"Production: "<< i + 1 ;
			cout<< " has left recursion";
			cout<< endl;
			
			k++;
			while(k<d.size() && d[k] != '|')
				a.push_back(d[k++]);
			a.push_back(d[0]);
			a += "'|";
		}
		k++;
	}
	a += "#";
	cout << b << endl;
	cout << a << endl;
	return 0;
}
