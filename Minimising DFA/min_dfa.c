#include<stdio.h>

int main(){
	FILE *ptr;
	char buff[100];
	int states = 0, alphabets, istate;
	int i,j,k;
	
	ptr = fopen("min_dfa.txt", "r");
	if(ptr == NULL){
		printf("Error opening the file.\n");
		return 0;
	}
	//Number of states.
	fscanf(ptr, "%[^\n]", buff);
	char c = fgetc(ptr);
	c = fgetc(ptr);
	states = (int)(c)-48;
	while((c = fgetc(ptr))!='\n'){
		states = states*10 + ((int)(c)-48);
	}
	printf("States = %d\n",states);
	
	int fstate[states];
		
	//Number of alphabets.
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	alphabets = (int)(c)-48;
	while((c = fgetc(ptr))!='\n'){
		alphabets = alphabets*10 + ((int)(c)-48);
	}
	printf("Aplhabets = %d\n",alphabets);
	
	//Transitions.	
	int transitions[states][alphabets];
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	for(i=0;i<states;i++){
		for(j=0;j<alphabets;j++){
			transitions[i][j]=((int)(c)-48);
			c=fgetc(ptr);
			c=fgetc(ptr);
		}
	}
	for(i=0;i<states;i++){
		for(j=0;j<alphabets;j++){
			printf("%d ",transitions[i][j]);
		}
		printf("\n");
	}
	
	//Initial state.
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	istate = (int)(c)-48;
	while((c = fgetc(ptr))!='\n'){
		istate = istate*10 + ((int)(c)-48);
	}
	printf("Initial state = %d\n",istate);
	
	//Final states.
	for(i=0;i<states;i++){
		fstate[i]=-2;
	}
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	int x=0;
	while(c!='\n' && c!='\0'){
		if(c!=' '){
			fstate[x] = ((int)(c)-48);
			x++;
		}
		c=fgetc(ptr);
	}
	for(i=0;i<states;i++){
		printf("%d ",fstate[i]);
	}
	
	return 0;
}
