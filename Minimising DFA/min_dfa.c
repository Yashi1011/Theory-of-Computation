#include<stdio.h>

int check_states(int states,int alphabets, int transitions[states][alphabets], int arr[states],int c,int min_states[states][states],int counter){
	int a,i,j;
	int sub_grp[c][c];
	for(i=0;i<c;i++){
		for(j=0;j<c;j++){
			sub_grp[i][j]=-2;
		}
	}
	for(a=0;a<alphabets;a++){
		int c0=0,c1=0;
		for(i=0;i<c;i++){
			for(j=0;j<states;j++){
				printf("%d %d\n",transitions[arr[i]][a],min_states[i][j] );
				if(transitions[arr[i]][a]==min_states[i][j]){
					c0++;
				}
			}
			if(c0==c){
				printf("Hey!!!");
				break;
			}
			
		}
		if(c0==c){
				printf("Hey!!!");
				break;
		}
		printf("\n");
	}
	return counter;
}

void minimize(int states, int alphabets, int transitions[states][alphabets], int istate, int fstate[states]){
	int min_states[states][states];
	int i,j;
	
	for(i=0;i<states;i++){
		for(j=0;j<states;j++){
			min_states[i][j]=-2;
		}
	}
	int c0=0,c1=0;
	for(i=0;i<states;i++){
		int flag=0;
		for(j=0;j<states;j++){
			if(i==fstate[j])
				flag=1;
		}
		if(flag==1){
			min_states[1][c1]=i;
			c1++;
		}
		else{
			min_states[0][c0]=i;
			c0++;
		}
	}
	printf("c0=%d c1=%d\n",c0,c1);
	for(i=0;i<states;i++){
		for(j=0;j<states;j++){
			printf("%d ",min_states[i][j]);
		}
		printf("\n");
	}
	int counter=2;
	i=0;
	while(i<counter){
		int arr[states], c, pre_counter;
		for(j=0;min_states[i][j]!=-2;j++){
			arr[j]=min_states[i][j];
		}
		c=j;
		pre_counter=counter;
		counter = check_states(states, alphabets, transitions, arr, c, min_states, counter);
		if(pre_counter==counter){
			i++;
		}
		//printf("%d ",c);
	}
}

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
	
	minimize(states, alphabets, transitions, istate, fstate);
	
	return 0;
}
