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
            
            if(strlen(word)!=0){
              	int flag=0;
              	for(k=0;k<pro[i].n;k++){
                	if(strcmp(pro[i].rhs[k],word)==0){
                 		flag=1;
          			}
        		}
        		if(flag==0){
          			strcpy(pro[i].rhs[pro[i].n],word);
                	pro[i].n++;
        		}
        	}
      
            if(c>=2){
              	int x,ind,y=0;
              	for(x=1;x<=c;x++){
                	m=0;
                	y=0;
                	for(k=0;k<strlen(pro[i].rhs[j]);k++){
                  		if(pro[i].rhs[j][k]==epsilon){
                    		y++;
            			}
            			if(y==x){
              				ind=k;
              				break;
            			}
                	}
            	    for(l=0;l<strlen(pro[i].rhs[j]);l++){
                  
            	        if(l!=ind){
                    	  	word[m]=pro[i].rhs[j][l];
                    	   	m++;
            			}
               		}
                	int flag=0;
                	for(k=0;k<pro[i].n;k++){
                		if(strcmp(pro[i].rhs[k],word)==0){
                    		flag=1;
            			}
          			}	
          			if(flag==0){
            			strcpy(pro[i].rhs[pro[i].n],word);
               		   	pro[i].n++;
          			}
                  
        		}
              
      		}
            
        }
        
    }

}

void add(int i,int a,int b,int c){
  	int l,m,n,flag=0,j,i_alt;
  	printf("----------%s -> %s\n",pro[a].lhs,pro[a].rhs[b]);
  	for(j=0;j<pro[i].n;j++){
  		printf("%d . %s\n",j,pro[i].rhs[j]);
        if(strlen(pro[i].rhs[j])==1 && pro[i].rhs[j][0]>='A' && pro[i].rhs[j][0]<='Z'){
        	for(l=0;l<cnt;l++){
        		if(strcmp(pro[i].rhs[j],pro[l].lhs)==0){
        			printf("--%s\n",pro[l].lhs);
        			i_alt=l;
        			printf("i_alt=%d\n",i_alt);
				}
			}
          	flag=1;
        }
        else{
        	int f=0;
        	if(c==0){
        		for(l=0;l<pro[a].n;l++){
        			if(strcmp(pro[i].rhs[j],pro[a].rhs[l])==0){
        				f=1;
					}
				}
				if(f!=1){
					strcpy(pro[a].rhs[b],pro[i].rhs[j]);
            		c++;
				}
            	
    		}
          	else{
          		for(l=0;l<pro[a].n;l++){
        			if(strcmp(pro[i].rhs[j],pro[a].rhs[l])==0){
        				f=1;
					}
				}
				if(f!=1){
            		strcpy(pro[a].rhs[pro[a].n],pro[i].rhs[j]);
            		pro[a].n++;
            		c++;
            	}
    		}
        }
        
    }
    printf("\nThe Grammar after removing 'Unit productions' is :-\n\n");
    for(i=0; i<cnt; i++){
      
        for(j=0; j<pro[i].n; j++){
        
            printf("%s -> %s\n", pro[i].lhs, pro[i].rhs[j]);

        }
    }
    if(flag==1){
    	printf("Calling again\n");
    	add(i_alt,a,b,c);
	}
	return;
  
}

void removeUnitProduction(){
  	int i,j,a,b;
  	for(a=1; a<cnt; a++){  
        for(b=0; b<pro[a].n; b++){
            if(strlen(pro[a].rhs[b])==1 && pro[a].rhs[b][0]>='A' && pro[a].rhs[b][0]<='Z'){
              	printf("%s -> %s\n",pro[a].lhs,pro[a].rhs[b]);
            	for(i=0;i<cnt;i++){
          			if(strcmp(pro[a].rhs[b],pro[i].lhs) == 0){
            			printf("%s\n",pro[i].lhs);
            			add(i,a,b,0);
                	}
              	}
            }
        }
    }
	
	for(b=0;b<pro[0].n;b++){
		if(strlen(pro[0].rhs[b])==1 && pro[0].rhs[b][0]>='A' && pro[0].rhs[b][0]<='Z'){
            printf("%s -> %s\n",pro[0].lhs,pro[0].rhs[b]);
            for(i=0;i<cnt;i++){
          		if(strcmp(pro[0].rhs[b],pro[i].lhs) == 0){
            		printf("%s\n",pro[i].lhs);
            		add(i,0,b,0);
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
                pro[a].n--;
                removeEpsilon(epsilon);
            }
        }
    }

    printf("\nThe Grammar after removing 'lambda productions' is :-\n\n");
    for(i=0; i<cnt; i++){
      
        for(j=0; j<pro[i].n; j++){
          
            printf("%s -> %s\n", pro[i].lhs, pro[i].rhs[j]);

        }
    }
    
    //Removal of unit produtions.
    
    removeUnitProduction();
    
    
    printf("\nThe Grammar after removing 'Unit productions' is :-\n\n");
    for(i=0; i<cnt; i++){
      
        for(j=0; j<pro[i].n; j++){
        
            printf("%s -> %s\n", pro[i].lhs, pro[i].rhs[j]);

        }
    }

}
