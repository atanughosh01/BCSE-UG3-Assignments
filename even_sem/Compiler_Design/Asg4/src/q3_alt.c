#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define PLEN 20
typedef struct
{
	int count;
	int rules[40][PLEN];
} production_rule;
production_rule rules[56];

int check_for_direct_left(int non_ter, production_rule *P)
{
	int l = P->count;
	while (l--)
	{
		if (P->rules[l][0] == non_ter)
			return 1;
	}
	return 0;
}

int is_in_left(int n, int sv)
{

	production_rule *P = rules + n;
	int(*rule)[PLEN] = P->rules, l = P->count;
	while (l--)
		if ((rule++)[0][0] == sv)
			return 1;

	return 0;
}

int *copyrule(int *dst, int *src)
{
	while (*src != -1)
		*(dst++) = *(src++);
	return dst;
}
void remove_direct_left_rec();
void remove_indirect(int nonter)
{
	for (int j = 0; j < nonter; j++)
	{
		production_rule temp = rules[nonter], *P = rules + nonter;
		int l = temp.count, (*rule)[PLEN] = temp.rules;
		P->count = 0;
		production_rule *Q = rules + j;
		while (l--)
		{
			if (rule[0][0] == j)
			{
				int l2 = Q->count;
				for (int k = 0; k < l2; k++)
					*copyrule(copyrule(P->rules[P->count++], Q->rules[k]), rule[0] + 1) = -1;
			}
			else
				*copyrule(P->rules[P->count++], rule[0]) = -1;
			rule++;
		}
	}
}

void remove_direct_left_rec(int non_ter)
{
	if (!check_for_direct_left(non_ter, rules + non_ter))
		return;
	production_rule temp = rules[non_ter], *P = rules + non_ter, *P_ = rules + non_ter + 26;
	P->count = 0;
	for (int i = 0; i < temp.count; i++)
	{
		if (temp.rules[i][0] == non_ter)
		{
			// A->AB transform to A'->BA'
			int *p = copyrule(P_->rules[P_->count++], temp.rules[i] + 1);
			*(p++) = non_ter + 26;
			*p = -1;
		}
		else
		{
			// A->B  transform A->BA'
			int *p = copyrule(P->rules[P->count++], temp.rules[i]);
			*(p++) = non_ter + 26;
			*p = -1;
		}
	}
	P_->rules[P_->count][0] = 'e';
	P_->rules[P_->count++][1] = -1;
	if (!P->count)
	{
		P->rules[0][0] = non_ter + 26;
		P->rules[0][1] = -1;
		P->count = 1;
	}
}
void print_production(int nonter)
{
	int(*rule)[PLEN] = rules[nonter].rules, l = rules[nonter].count;
	if (!l)
		return;
	if (nonter < 26)
	{
		printf("%c->", nonter + 'A');
	}
	else
		printf("%c'->", nonter + 'A' - 26);
	while (l--)
	{
		int *ptr = (int *)rule;
		while (*ptr != -1)
		{
			if (islower(*ptr))
				printf("%c", *ptr);
			else if (*ptr < 26)
				printf("%c", *ptr + 'A');
			else
				printf("%c'", *ptr + 'A' - 26);
			ptr++;
		}
		printf("%c", l ? '|' : '\n');
		rule++;
	}
}

int main(int argc, char **argv)
{
	for (int i = 0; i < 56; i++)
		rules[i].count = 0;
	FILE *f = argc > 1 ? fopen(argv[1], "r") : stdin;
	if (!f)
	{
		perror("Cannot open input file\n");
		return 1;
	}
	char buffer[20];
	while (fscanf(f, "%[^\n]%*c", buffer) != EOF)
	{
		int non = buffer[0] - 'A';
		char *ch = buffer + 3;
		production_rule *P = rules + non;
		while (*ch)
		{
			int *ptr = P->rules[P->count++];
			while (*ch && *ch != '|')
			{
				if (islower(*ch))
					*(ptr++) = *(ch++);
				else
					*(ptr++) = *(ch++) - 'A';
			}
			*ptr = -1;
			if (*ch == '|')
				ch++;
		}
	}
	fclose(f);

	/* indirect removal */
	for (int i = 0; i < 26; i++)
		remove_indirect(i);
	/* direct removal */
	for (int i = 0; i < 26; i++)
		remove_direct_left_rec(i);
	if (f == stdin)
	{
		printf("+---Grammar after removing Left Recursion---+\n");
	}
	/* printing */
	for (int i = 0; i < 56; i++)
		print_production(i);
	return 0;
}
