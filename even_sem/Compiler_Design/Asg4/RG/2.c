#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
/*
 
 * Grammar for accepting algebraic expression(without whitespaces)
 	
 	E –> E + T | T 
	T –> T * F | F 
	F –> ( E ) | id

 * Same Grammar after left recursion removal
 
	E->TE'
	E'->+TE'|e
	T->FT'
	T'->*FT'|e
	F->id|const|(E)

*/

char *ch;
int err;
void E();
void E_();
void T();
void T_();
void F();

void E()
{
	T();
	E_();
}
void E_()
{
	if (*ch == '+')
	{
		ch++;
		T();
		E_();
	}
	else
		return;
}
void T()
{
	F();
	T_();
}
void T_()
{
	if (*ch == '*')
	{
		ch++;
		F();
		T_();
	}
	else
		return;
}
void F()
{
	if (isalpha(*ch))
	{
		while (isalnum(*ch) || *ch == '_')
			ch++;
	}
	else if (isdigit(*ch))
	{
		while (isdigit(*ch))
			ch++;
	}
	else if (*ch == '(')
	{
		ch++;
		E();
		if (*ch == ')')
			ch++;
		else
			err = 1;
	}
	else
		err = 1;
}

int main()
{
	char buffer[100];
	scanf("%[^\n]%*c", buffer);
	while (buffer[0] != '-')
	{
		err = 0;
		ch = buffer;
		E();
		if (err || *ch != '\0')
			printf("NOT ACCEPTED\n");
		else
			printf("ACCEPTED\n");
		scanf("%[^\n]%*c", buffer);
	}
}
