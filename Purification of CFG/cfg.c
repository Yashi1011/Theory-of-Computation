//Purification of Context-Free-Grammar.


//Importing the libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Decalring global variables/arrays.
int cnt=0;
char epsilon;


//Defining a structure array for productions.
struct Production
{

    char lhs[10], rhs[20][10];
    int n;

}pro[10];

void remove_moreps(int i,int j,int c){
	
}

//Removal of epsilon productions.
void removeEpsilon(char epsilon){
	int i,j,k,l;
	
    for(i=0; i<cnt; i++){
    	
        for(j=0; j<pro[i].n; j++){
        	
            int m=0,c=0;
            char word[10]="";
            for(k=0; k<strlen(pro[i].rhs[j]); k++){
                if(pro[i].rhs[j][k]==epsilon){
                	c++;
                	if(c==1){
                		for(l=0;l<strlen(pro[i].rhs[j]);l++){
                			if(pro[i].rhs[j][l]!=epsilon){
                				word[m]=pro[i].rhs[j][l];
                    			m++;
							}
                		
						}
						
					}
                	
                }
            
            }
            
            printf("%s\n",word);
            if(strlen(word)!=0){
            	int flag=0;
            	for(k=0;k<pro[i].n;k++){
            		if(strcmp(pro[i].rhs[k],word)==0){
            			flag=1;
					}
				}
				if(flag==0){
					strcpy(pro[i].rhs[pro[i].n],word);
            		printf("--%s\n",pro[i].rhs[pro[i].n]);
            		pro[i].n++;
				}
           	}
			
            if(c>=2){
            	printf("c=%d\n",c);
            	int x,ind,y=0;
            	//remove_moreps(i,j,c);
            	for(x=1;x<=c;x++){
            		m=0;
            		y=0;
            		for(k=0;k<strlen(pro[i].rhs[j]);k++){
            			if(pro[i].rhs[j][k]==epsilon){
            				y++;
						}
						if(y==x){
							ind=k;
							printf("k=%d\n",k);
							break;
						}
            		}
            		for(l=0;l<strlen(pro[i].rhs[j]);l++){
            			
                		if(l!=ind){
                			word[m]=pro[i].rhs[j][l];
                    		m++;
						}
                	}
                	strcpy(pro[i].rhs[pro[i].n],word);
            		printf("--%s\n",pro[i].rhs[pro[i].n]);
            		pro[i].n++;
                	
				}
            	
			}
            
        }
        
    }

}


//Main function.
int main() 
{

    //Declaring a file pointer.
    FILE *f;
	int i,j,k,a,b;
    //Initialising the number in productions to 0.
    for(i=0; i<10; i++)
        pro[i].n=0;

    //Opening the file.
    f = fopen("4.txt", "r");

    //Reading the contents of the file.
    while(!feof(f)) 
    {
        //Storing the LHS of the production.
        fscanf(f, "%s", pro[cnt].lhs);
        if(cnt>0) 
        {
            if(strcmp(pro[cnt].lhs, pro[cnt-1].lhs)==0) 
            {
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
    for(i=0; i<cnt; i++)
    {
        for(j=0; j<pro[i].n; j++)
        {
            printf("%s -> %s\n", pro[i].lhs, pro[i].rhs[j]);
        }
    }

    //Removal of epsilon productions.
    for(a=0; a<cnt; a++)
    {
        for(b=0; b<pro[a].n; b++)
        {
            if(pro[a].rhs[b][0]=='#')
            {
                epsilon=pro[a].lhs[0];
                printf("\nEpsilon = %c\n",epsilon);
                removeEpsilon(epsilon);
            }
        }
    }

    printf("\nThe final Grammar is :-\n\n");
    for(i=0; i<cnt; i++)
    {
        for(j=0; j<pro[i].n; j++)
        {
            if(pro[i].rhs[j][0]!='#' && pro[i].rhs[j][0]!=' ')
                printf("%s -> %s\n", pro[i].lhs, pro[i].rhs[j]);

        }
    }
    

}
