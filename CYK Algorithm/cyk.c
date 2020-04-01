#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Production
{

    char lhs[10], rhs[10][10];
    int n;

}pro[10];

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
	printf("count = %d",cnt);
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
    
    int n = strlen(str);
    
    char v[n][n][10];
    
    for(i=0;i<n;i++){
    	for(j=0;j<n;j++){
    		strcpy(v[i][j],"\0");
		}
    }
	
    for(i=0;i<n;i++){
    	for(x=0; x<cnt; x++){
    	    for(y=0; y<pro[x].n; y++){
            	if(pro[x].rhs[y][0]==str[i]){
                	char e=pro[x].lhs[0];
                	for(k=0;v[i][1][k]!='\0';k++){
					}
					v[i][1][k]=e;
					v[i][1][k+1]='\0';
            	}
        	}
		}
	}
	
	
    for(i=0;i<n;i++){
    	printf("-->%s\n",v[i][1]);
	}
}
