//Converting an NFA to DFA.

#include <stdio.h>

int main()
{

	//Declaring variables and pointers.
	char buff[20],state[10],final_state;
	char transition[3][2];
	int state_counter=0,i;
	FILE *ptr;

	//Reading input from the file.
	ptr = fopen("nfa_input.txt", "r");

	//Checking if the pointer is NULL or not.
	if(ptr == NULL)
		printf("Error occurred while opening the file\n");
	else
	{
		//States.
		fscanf(ptr, "%s", buff);

		char c=fgetc(ptr);
		while((c=fgetc(ptr))!='\n')
		{
			if(c!=' '){
				state[state_counter]=c;
				state_counter++;
			}
		}
		c=fgetc(ptr);

		//Transitions.
		fgets(buff, 20, ptr);

		c=fgetc(ptr);
		for(i=0; i<3; i++)
		{
			while((c=fgetc(ptr))!='\n')
			{
				if()
			}
		}

		fclose(ptr);
	}

}