#include <stdio.h>
#include <stdlib.h>

struct Stack
{
	char stack[100];
	int top;
	int cnt;
}s;

void push(char c)
{
	s.stack[++s.top]=c;
	s.cnt++;
}

char pop()
{
	s.cnt--;
	return s.stack[s.top--];
}

int i=0;
char word[50];

void check_a()
{
	while(word[i]=='b')
	{
		char ch=pop();
		if(ch!='a')
		{
			printf("Wrong word\n");
			exit(0);
		}
		i++;
	}
	printf("Word is accepted\n");
	exit(0);
}

void check_b()
{
	while(word[i]=='a')
	{
		char ch=pop();
		if(ch!='b')
		{
			printf("Wrong word\n");
			exit(0);
		}
		i++;
	}
	check_a();
}

void insert_b()
{
	while(word[i]=='b')
	{
		push('b');
		i++;
	}
	check_b();
}

void insert_a()
{
	while(word[i]=='a')
	{
		push('a');
		i++;
	}
	insert_b();
}

int main()
{
	s.top=-1;
	s.cnt=0;
	printf("Enter the word in a^n b^m a^m b^n format: ");
	scanf("%s",word);
	if(word[0]=='a')
	{
		insert_a();
	}
	else
	{
		printf("n is a positive integer and can't be zero\n");
	}
}
