//a^n b^m a^m b^n
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



int main()
{
	s.top=-1;
	s.cnt=0;
	int i,j,k;
	char word[50];
	printf("Enter the word in a^n b^m a^m b^n format: ");
	scanf("%s",word);
	for(i=0; word[i]!='\0'; i++)
	{
		if(word[i]=='a' || word[i]=='b')
		{
			if(word[i]=='a')
			{
				int x=0;
				for(j=0; j<i; j++)
				{
					if(word[j]!='b')
					{
						x++;
					}
				}
				if(x==i)
				{
					push(word[i]);
				}
				else
				{
					char y=pop();
					if(y=='b')
					{
						continue;
					}
					else
					{
						printf("Wrong word");
						exit(0);
					}
				}
			}
			else if(word[i]=='b')
			{
				if(i>0)
				{
					int x=0;
					for(j=0; j<i; j++)
					{
						if(word[j]=='b')
						{
							break;
						}
					}
					for(k=j;k<i;k++){
						if(word[k]!='a'){
							x++;
						}
					}
					if(x==i-j)
					{
						push(word[i]);
					}
					else
					{
						char y=pop();
						if(y=='a')
						{
							continue;
						}
						else
						{
							printf("Wrong word");
							exit(0);
						}
					}
				}
				else
				{
					printf("\nn is a positive integer and can't be zero\n");
					exit(0);
				}
			}
			printf("%d\n",i);
			for(k=0;k<s.cnt;k++){
				printf("%c ",s.stack[k]);
			}
			printf("\n");
		}
		else
		{
			printf("\nWrong string entered\n");
			exit(0);
		}
	}
	if(s.cnt!=0)
		printf("Wrong word\n");
	else
		printf("Right word\n");
}
