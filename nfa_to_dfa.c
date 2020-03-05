//Converting an NFA to DFA.

#include<stdio.h>

int nfa_state[10],nfa_istate,nfa_fstate,state_counter=0,alphabets,i,j,k;
FILE *ptr;
char buff[20];
int transitions[3][2][3];

void getdata(){
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
				nfa_state[state_counter]=(int)(c)-48;
				state_counter++;
			}
		}
		c=fgetc(ptr);

		//Alphebets
		fgets(buff, 20, ptr);

		c=fgetc(ptr);
		alphabets = (int)(c)-48;
		
		c=fgetc(ptr);
		
		//Transitions.
		fgets(buff, 20, ptr);

		c=fgetc(ptr);
		
		for(i=0; i<state_counter; i++){
			for(j=0;j<alphabets;j++){
				for(k=0;k<state_counter;k++){
					transitions[i][j][k]=-2;
				}
			}
		}
	
		fgets(buff, 20, ptr);
		
		c=fgetc(ptr);
		for(i=0; i<state_counter; i++){
			j=0;
			while(c!='\n'){
				k=0;
				while(c!='-' && c!='\n'){
					if(c!=' '){
						if(c=='#'){
							transitions[i][j][k]=-1;
							k++;
						}
						else{
							transitions[i][j][k]=(int)(c)-48;
							k++;
						}
					}
					c=fgetc(ptr);
				}
				j++;
				c=fgetc(ptr);
			}
		}
		
		c=fgetc(ptr);
		
		//Initial state
		fgets(buff, 20, ptr);

		c=fgetc(ptr);
		nfa_istate=(int)(c)-48;	
		
		c=fgetc(ptr);
		
		//Final state
		c=fgetc(ptr);
		fgets(buff, 20, ptr);

		c=fgetc(ptr);
		nfa_fstate=(int)(c)-48;	

		fclose(ptr);
	}
}

void main(){
	getdata();
	for(i=0;i<state_counter;i++){
		printf("%d\n",nfa_state[i]);
	}
	printf("%d\n",alphabets);
	for(i=0; i<state_counter; i++){
		for(j=0;j<alphabets;j++){
			for(k=0;k<state_counter;k++){
				printf("%d ",transitions[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("%d\n%d\n",nfa_istate,nfa_fstate);
}
