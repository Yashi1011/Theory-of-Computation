//Purification of Context-Free-Grammar.


//Importing the libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Decalring global variables/arrays.
int i,j,k,l,m,o,p,nv,z=0,t,cnt=0,x=0;
char word[10], temp1[20], temp2[20], temp3[20];


//Defining a structure array for productions.
struct Production
{

    char lhs[10], rhs[10][10];
    int n;

}pro[10];


//Removal of epsilon productions.
void removeEpsilon(char epsilon)
{

    for(i=0; i<cnt; i++)
    {
        for(j=0; j<pro[i].n; j++)
        {
            for(int k=0; k<strlen(pro[i].rhs[j]); k++)
            {
                if(pro[i].rhs[j][k]==epsilon) 
                {
                    strcpy(pro[i].rhs[j],pro[i].rhs[pro[i].n]);
                    printf("\nAdd - %s",pro[i].rhs[j]);
                    break;
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
    printf("\n\nThe Grammar is :-\n\n");
    for(i=0; i<cnt; i++)
    {
        for(j=0; j<pro[i].n; j++)
        {
            printf("%s -> %s\n", pro[i].lhs, pro[i].rhs[j]);
        }
    }

    char epsilon;
    //Removal of epsilon productions.
    for(i=0; i<cnt; i++)
    {
        for(j=0; j<pro[i].n; j++)
        {
            if(strcmp(pro[i].rhs[j],"#")==0)
            {
                epsilon=pro[i].lhs[0];
                printf("\nEpsilon = %c\n",epsilon);
                removeEpsilon(epsilon);
            }
        }
    }

}
