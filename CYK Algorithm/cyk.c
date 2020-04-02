//CYK Algorithm.

//Including all the required libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structure to store productions.
struct Production{
	char lhs[10], rhs[10][10];
    	int n;
}pro[10];

//Function to order and remove duplicates of the Vij.
void order(char *str){
	int i, j;
   	int n = strlen(str);
	char temp;

   	for(i=0; i<n-1; i++) {
      		for (j=i+1; j<n; j++) {
         		if (str[i] > str[j]) {
            		temp = str[i];
            		str[i] = str[j];
            		str[j] = temp;
        		}
      		}
   	}
   	
   	if(strlen(str)==0 || strlen(str)==1){
   		return;
	}
	
	j = 0;
   	for(i=0;i<n-1;i++){
   		if (str[i] != str[i+1])
			str[j++] = str[i];
	}
	str[j++]=str[n-1];
	str[j]='\0';
}

//Function to find the union of Vij.
void vij_union(char a[10], char b[10], int cnt, int p, int q, int n, char v[n][n][10]){
	int i,j,x,y;
	char s[10];
	char str[10];
	strcpy(str,"\0");
	for(i=0;i<strlen(a);i++){
		for(j=0;j<strlen(b);j++){
			s[0]=a[i];
			s[1]=b[j];
			s[2]='\0';
			for(x=0; x<cnt; x++){
    	    			for(y=0; y<pro[x].n; y++){
            				if(strcmp(pro[x].rhs[y],s)==0){
            					strcat(str,pro[x].lhs);
            				}
        			}
			}
		}
	}
	strcat(str,v[p][q]);
	order(str);
	strcpy(v[p][q],str);
	
}

int main() 
{
	int i,j,k,x,y,cnt=0;
    	//Declaring a file pointer.
    	FILE *f;

   	//Initialising the number in productions to 0.
    	for(i=0; i<10; i++)
        pro[i].n=0;

    	//Opening the file.
    	f = fopen("CYK.txt", "r");

    	//Reading the contents of the file.
    	while(!feof(f)){
        	//Storing the LHS of the production.
        	fscanf(f, "%s", pro[cnt].lhs);
        	if(cnt>0){
            		if(strcmp(pro[cnt].lhs, pro[cnt-1].lhs)==0){
                		pro[cnt].lhs[0]='\0';
                		fscanf(f, "%s", pro[cnt-1].rhs[pro[cnt-1].n]);
                		pro[cnt-1].n++;
                		continue;
            		}
        	}
        	//Storing the RHS of the production.
        	fscanf(f, "%s", pro[cnt].rhs[pro[cnt].n]);
        	pro[cnt].n++;
        	cnt++;
    	}
    	cnt--;
    	//Printing the grammar.
    	printf("\nThe initial Grammar is :-\n\n");
    	for(i=0; i<cnt; i++){
        	for(j=0; j<pro[i].n; j++){
            	printf("%s -> %s\n", pro[i].lhs, pro[i].rhs[j]);
        	}
    	}
	
    	char str[20];
   	printf("\n\nEnter a string : ");
    	scanf("%s",&str);
	
    	//Finding the length g given string.
    	int n = strlen(str)+1;
	
    	//Creating an multi-dimentional array of strings to store Vij's.
    	char v[n][n][10];
    	
	//Beginning of CYK algo.
    	for(i=1;i<n;i++)
	    	for(j=1;j<n;j++){
		    	strcpy(v[i][j],"\0");
	    	}
    	}
	
    	for(i=0;i<n;i++){
    		for(x=0; x<cnt; x++){
    	    		for(y=0; y<pro[x].n; y++){
            			if(pro[x].rhs[y][0]==str[i]){
                			char e=pro[x].lhs[0];
                			for(k=0;v[i+1][1][k]!='\0';k++){
					}
					v[i+1][1][k]=e;
					v[i+1][1][k+1]='\0';
            			}
        		}
		}
	}
	
	char s1[10],s2[10];
	for(j=2;j<n;j++){
		for(i=1;i<(n-j+1);i++){
			for(k=1;k<=(j-1);k++){
				strcpy(s1,v[i][k]);
				strcpy(s2,v[i+k][j-k]);
				vij_union(s1,s2,cnt,i,j,n,v);
			}
		}
	}

	//Printing the table.
	printf("\n\nTABLE :\n\n");
	for(i=0;str[i]!='\0';i++){
		printf("%c\t",str[i]);
	}
	printf("\n\n");
	for(j=1;j<n;j++){
		for(i=1;i<(n-j+1);i++)
    			printf("%s\t",v[i][j]);
    		printf("\n\n");	
	}
	
	//Checking if he given string is a word in that Language.
	int flag = 0;
	strcpy(s1,v[1][n-1]);
	for(i=0;s1[i]!='\0';i++){
		if(s1[i]=='S'){
			flag=1;
		}
	}
	if(flag==1){
		printf("%s is accepted by language.\n",str);
	}
	else{
		printf("%s is NOT accepted by language.\n",str);
	}
	
}
