//Minimising the DFA.


//Importing the libraries.
#include<stdio.h>


//Function to order the minimized states.
void order(int states,int min_states[states][states],int imp)
{

	int i,c=0,a[states];
	for(i=0;i<states;i++)
		a[i]=-2;

	for(i=0;i<states;i++)
	{
		if(min_states[imp][i]!=-2)
		{
			a[c]=min_states[imp][i];
			c++;
		}
	}

	for(i=0;i<states;i++)
		min_states[imp][i]=a[i];

}


//Function to print the final DFA.
void print(int alphabets,int states,int counter,int min_states[states][states],int min_transitions[states][alphabets], int min_istate, int min_fstate[states])
{

	int i,j;

	printf("\nMinimised states: \n\n");
	for(i=0;i<counter;i++)
	{
		printf("State %d = { ",i);
		for(j=0;min_states[i][j]!=-2;j++)
		{
			printf("%d ",min_states[i][j]);
		}
		printf("}\n");
	}

	printf("\nTransitions: \n\n");

	printf("State\t");
	for(i=0;i<alphabets;i++)
	{
		printf("alp%d\t",i+1);
	}
	printf("\n");

	for(i=0;i<counter;i++)
	{
		printf("%d\t",i);
		for(j=0;j<alphabets;j++)
		{
			printf("%d\t",min_transitions[i][j]);
		}
		printf("\n");
	}

	printf("\nInitial state : state %d\n",min_istate);
	printf("\nFinal state(s) : \n");

	for(i=0;min_fstate[i]!=-2;i++)
	{
		printf("state %d\n",min_fstate[i]);
	}

}


//Function to split the groups of states.
int check_states(int states,int alphabets, int transitions[states][alphabets], int arr[states],int c,int min_states[states][states],int counter,int imp, int min_transitions[states][alphabets])
{

	int a,i,j,k,l;
	int sub[alphabets][c];
	
	for(i=0;i<alphabets;i++)
	{
		for(j=0;j<c;j++)
		{
			sub[i][j]=transitions[arr[j]][i];
		}
	}
	
	int flag=0,x=0;
	for(k=0;k<alphabets;k++)
	{
		int s;
		for(l=0;l<c;l++)
		{
			for(i=0;i<counter;i++)
			{
				for(j=0;j<states;j++)
				{
					if(min_states[i][j]==sub[k][l])
					{
						s=i;
						break;
					}
				}
			}
		}
		min_transitions[imp][k]=s;
		for(l=0;l<c;l++)
		{
			for(i=0;i<counter;i++)
			{
				for(j=0;j<states;j++)
				{
					if(min_states[i][j]==sub[k][l] && s!=i)
					{
						min_states[counter][x]=arr[l];
						min_states[imp][l]=-2;
						flag=1;
						x++;
					}
				}
			}
		}
	}

	if(flag==1)
		counter++;

	order(states,min_states,imp);

	return counter;

}


//Funtion to start the minimization of given DFA.
void minimize(int states, int alphabets, int transitions[states][alphabets], int istate, int fstate[states])
{

	int min_states[states][states];
	int i,j,x,k;
	int min_transitions[states][alphabets], min_istate, min_fstate[states];
	
	for(i=0;i<states;i++)
	{
		for(j=0;j<states;j++)
		{
			min_states[i][j]=-2;
		}
	}
	
	int c0=0,c1=0;
	for(i=0;i<states;i++)
	{
		int flag=0;
		for(j=0;j<states;j++)
		{
			if(i==fstate[j])
				flag=1;
		}
		if(flag==1)
		{
			min_states[1][c1]=i;
			c1++;
		}
		else
		{
			min_states[0][c0]=i;
			c0++;
		}
	}

	int counter=2;
	i=0;
	while(i<counter && i<states)
	{
		int arr[states], c=0, pre_counter;
		
		for(j=0;j<states;j++)
		{
			if(min_states[i][j]!=-2)
			{
				arr[c]=min_states[i][j];
				c++;
			}
		}
		
		pre_counter=counter;
		counter = check_states(states, alphabets, transitions, arr, c, min_states, counter,i,min_transitions);
		
		if(pre_counter==counter)
			i++;
		else
			i=0;
	}
	
	for(i=0;i<counter;i++)
	{
		for(j=0;j<states;j++)
		{
			if(istate==min_states[i][j])
			{
				min_istate=i;
				break;
			}
		}
	}
	
	for(i=0;i<states;i++)
	{
		min_fstate[i]=-2;
	}

	x=0;
	for(i=0;i<counter;i++)
	{
		for(j=0;min_states[i][j]!=-2;j++)
		{
			for(k=0;fstate[k]!=-2;k++)
			{
				if(min_states[i][j]==fstate[k])
				{
					min_fstate[x]=i;
					x++;
					break;
				}
			}
			break;	
		}
	}
	
	print(alphabets,states,counter,min_states,min_transitions,min_istate, min_fstate);

}


//Main function.
int main()
{

	FILE *ptr;
	char buff[100];
	int states = 0, alphabets, istate;
	int i,j,k;
	
	ptr = fopen("3.txt", "r");
	if(ptr == NULL)
	{
		printf("Error opening the file.\n");
		return 0;
	}

	//Number of states.
	fscanf(ptr, "%[^\n]", buff);
	char c = fgetc(ptr);
	c = fgetc(ptr);
	states = (int)(c)-48;
	while((c = fgetc(ptr))!='\n')
	{
		states = states*10 + ((int)(c)-48);
	}
	
	int fstate[states];
		
	//Number of alphabets.
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	alphabets = (int)(c)-48;
	while((c = fgetc(ptr))!='\n')
	{
		alphabets = alphabets*10 + ((int)(c)-48);
	}
	
	//Transitions.	
	int transitions[states][alphabets];
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	for(i=0;i<states;i++)
	{
		for(j=0;j<alphabets;j++)
		{
			transitions[i][j]=((int)(c)-48);
			c=fgetc(ptr);
			c=fgetc(ptr);
		}
	}
	
	//Initial state.
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	istate = (int)(c)-48;
	while((c = fgetc(ptr))!='\n')
	{
		istate = istate*10 + ((int)(c)-48);
	}
	
	//Final states.
	for(i=0;i<states;i++)
	{
		fstate[i]=-2;
	}
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	int x=0;
	while(c!='\n' && c!='\0')
	{
		if(c!=' ')
		{
			fstate[x] = ((int)(c)-48);
			x++;
		}
		c=fgetc(ptr);
	}
	
	minimize(states, alphabets, transitions, istate, fstate);
	
	return 0;

}
