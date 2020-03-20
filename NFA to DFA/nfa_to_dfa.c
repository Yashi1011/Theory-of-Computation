#include<stdio.h>

count=-1;

int counter(int alp){
	count++;
	return count/alp;
}
  
void swap(int *xp, int *yp){ 
	int temp = *xp; 
	*xp = *yp; 
	*yp = temp; 
} 
  

void sort(int arr[], int n) { 
	int i, j; 
	for (i = 0; i < n-1; i++){
		for (j = 0; j < n-i-1; j++){
			if (arr[j] > arr[j+1]){
				swap(&arr[j], &arr[j+1]);
			}
		}
	}             
}

int removeDuplicates(int arr[], int n) 
{ 
    if (n==0 || n==1) 
        return n;
    
    int i,j = 0; 
    for (i=0; i < n-1; i++) 
        if (arr[i] != arr[i+1]) 
            arr[j++] = arr[i]; 
  
    arr[j++] = arr[n-1];
    if(arr[0]==-1){
    	for(i=0;i<j-1;i++){
    		arr[i]=arr[i+1];
		}
		return j-1;
	}
	else{
		return j;
	}    
} 

int transition(int state[],int nfa_states,int alphabets,int nfa_transitions[nfa_states][alphabets][nfa_states],int dfa_state[3][nfa_states],int state_counter,int dfa_transitions[3][alphabets]){
	int x=0,i=0,j,k=0,z;
	int a[100];
	for(i=0;i<alphabets;i++){
		k=0;
		x=0;
		while(state[x]!=-2){
			for(j=0;j<nfa_states;j++){
				if(nfa_transitions[state[x]][i][j]!=-2){
					a[k] = nfa_transitions[state[x]][i][j];
					k++;
				}
			}
			x++;
		}
		sort(a,k);
		k = removeDuplicates(a,k);
		int flag=0, t_state;
		for(z=0;z<state_counter;z++){
			int c1=0;
			for(j=0;j<k;j++){
				if(dfa_state[z][j]==a[j]){
					c1=c1+1;
				}
			}
			if(c1==k){
				t_state=z;
				flag=0;
				break;
			}
			else{
				flag=1;
			}
		}
		if(flag == 1){
			t_state=state_counter;
			for(j=0;j<k;j++){
				dfa_state[state_counter][j] = a[j];
			}
			state_counter++;
		}
		dfa_transitions[counter(alphabets)][i] = t_state;
	}

	return state_counter;
}

print_nfa(int state_counter,int nfa_states,int alphabets,int dfa_state[3][nfa_states],int dfa_transitions[3][alphabets]){
	int i,j;
	printf("DFA of given NFA :\n\nSTATE");
	for(j=0;j<alphabets;j++){
		printf("\t\t\tALP%d",j+1);
	}
	printf("\n");
	for(i=0;i<state_counter;i++){
		printf("State %d : ",i);
		for(j=0;j<alphabets;j++){
			if(dfa_state[i][j]!=-2){
				printf("%d ",dfa_state[i][j]);
			}
		}
		printf("\t\t");
		for(j=0;j<alphabets;j++){
			printf("%d\t\t",dfa_transitions[i][j]);
		}
		printf("\n\n");
	}
}


void convert_dfa(int nfa_states,int alphabets,int nfa_transitions[nfa_states][alphabets][nfa_states],int nfa_istate, int nfa_fstate[], int no_fstates){
	int i=0,j=0,k;
	int dfa_istate = nfa_istate;
	int dfa_state[3][nfa_states];
	int dfa_transitions[3][alphabets];
	
	for(i=0;i<3;i++){
		for(j=0;j<nfa_states;j++){
			dfa_state[i][j]=-2;
		}
	}
	
	int state_counter = 1;
	
	dfa_state[0][0] = nfa_istate;
	
	int state[nfa_states];
	for(i=0;i<3;i++){
		for(j=0;j<nfa_states;j++){
			state[j]=dfa_state[i][j];
				
		}
		state_counter = transition(state, nfa_states, alphabets, nfa_transitions, dfa_state,state_counter,dfa_transitions);
	}
	
	for(i=0;i<3;i++){
		for(j=0;j<nfa_states;j++){
			printf("%d ",dfa_state[i][j]);
		}
		printf("\n");
	}
	
	print_nfa(state_counter, nfa_states, alphabets,dfa_state,dfa_transitions);
	
}

int main(){
	FILE *ptr;
	char buff[100];
	int nfa_states = 0, alphabets, nfa_istate;
	int i,j,k;
	
	ptr = fopen("nfa.txt", "r");
	if(ptr == NULL){
		printf("Error opening the file.\n");
		return 0;
	}
	//Number of states.
	fscanf(ptr, "%[^\n]", buff);
	char c = fgetc(ptr);
	c = fgetc(ptr);
	nfa_states = (int)(c)-48;
	while((c = fgetc(ptr))!='\n'){
		nfa_states = nfa_states*10 + ((int)(c)-48);
	}
	
	int nfa_fstate[nfa_states];
		
	//Number of alphabets.
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	alphabets = (int)(c)-48;
	while((c = fgetc(ptr))!='\n'){
		alphabets = alphabets*10 + ((int)(c)-48);
	}
	
	//Transitions.	
	int nfa_transitions[nfa_states][alphabets][nfa_states];
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	for(i=0; i<nfa_states; i++){
		for(j=0;j<alphabets;j++){
			for(k=0;k<nfa_states;k++){
				nfa_transitions[i][j][k]=-2;
			}
		}
	}
	for(i=0; i<nfa_states; i++){
		j=0;
		while(c!='\n'){
			k=0;
			while(c!='-' && c!='\n'){
				if(c!=' '){
					if(c=='#'){
						nfa_transitions[i][j][k]=-1;
						k++;
					}
					else{
						nfa_transitions[i][j][k]=(int)(c)-48;
						k++;
					}
				}
				c=fgetc(ptr);
			}
			j++;
			if(c=='\n')
				break;
			c=fgetc(ptr);
		}
		c=fgetc(ptr);
	}
	
	//Initial state.
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	nfa_istate = (int)(c)-48;
	while((c = fgetc(ptr))!='\n'){
		nfa_istate = nfa_istate*10 + ((int)(c)-48);
	}
	
	//Final states.
	fscanf(ptr, "%[^\n]", buff);
	c = fgetc(ptr);
	c = fgetc(ptr);
	int x=0;
	while(c!='\n'){
		if(c!=' '){
			nfa_fstate[x] = ((int)(c)-48);
			x++;
		}
		c=fgetc(ptr);
	}
	
	convert_dfa(nfa_states, alphabets, nfa_transitions, nfa_istate, nfa_fstate,x);
	
}
