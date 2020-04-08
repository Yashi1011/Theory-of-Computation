//Constructing a Push Down Automata for a^n b^m a^m b^n.


//Importing the libraries.
#include <stdio.h>
#include <stdlib.h>


//Defining a structure for stack.
struct Stack
{
	char stack[100];
	int top;
	int cnt;
}s;


//Push into the stack.
void push(char c)
{
	s.stack[++s.top]=c;
	s.cnt++;
}


//Pop from the stack.
char pop()
{
	s.cnt--;
	return s.stack[s.top--];
}


//Declaring global values.
int i=0;
char word[50];


//Checking b^n.
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
	if(s.cnt==0)
		printf("Word is accepted\n");
	else
		printf("Wrong word\n");
	exit(0);
}


//Check a^m.
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


//Inserting b^m.
void insert_b()
{
	while(word[i]=='b')
	{
		push('b');
		i++;
	}
	check_b();
}


//Inserting a^n.
void insert_a()
{
	while(word[i]=='a')
	{
		push('a');
		i++;
	}
	insert_b();
}


//Main funtion.
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
		printf("Wrong format\n");
	}
}
