//Converting an NFA to DFA.

#include<stdio.h>

  
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
  
    return j; 
} 


void check_state(int a[], int n,int *dfa_state[3][n],int k){
	int i,j;
	sort(a,k);
	for(i=0;i<k;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	k = removeDuplicates(a,k);
	printf("k=%d\n",k);
	for(i=0;i<k;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	for(i=0;i<3;i++){
		for(j=0;j<k;j++){
			printf("%d ",dfa_state[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<3;i++){
		int c1=0;
		for(j=0;j<k;j++){
			if(dfa_state[i][j]==a[j]){
				c1=c1+1;
			}
		}
		printf("%d\n",c1);
		if(c1==k){
			printf("Exists\n");
		}
		else{
			printf("doesn't exist\n");
		}
	}
}

void transition(int state[],int nfa_states,int alphabets,int nfa_transitions[nfa_states][alphabets][nfa_states],int *dfa_state[3][nfa_states]){
	int x=0,i=0,j,k=0;
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
		check_state(a,nfa_states,dfa_state,k);
	}
}


void convert_dfa(int nfa_states,int alphabets,int nfa_transitions[nfa_states][alphabets][nfa_states],int nfa_istate, int nfa_fstate[], int no_fstates){
	int i=0,j=0,k;
	int dfa_istate = nfa_istate;
	int dfa_state[3][nfa_states];
	
	for(i=0;i<3;i++){
		for(j=0;j<nfa_states;j++){
			dfa_state[i][j]=-2;
		}
	}
	
	dfa_state[0][0] = nfa_istate;
	
		int state[nfa_states];
		for(i=0;i<3;i++){
			for(j=0;j<nfa_states;j++){
				state[j]=dfa_state[i][j];
				
			}
			transition(state, nfa_states, alphabets, nfa_transitions, dfa_state);
		}
	
//	for (i = 0; i < nfa_states; i++){
//		for(j=0;j<alphabets;j++){
//			for(k=0;k<nfa_states;k++){
//				printf("%d ",nfa_transitions[i][j][k] );
//				
//			}
//		}	
//	}

	
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
