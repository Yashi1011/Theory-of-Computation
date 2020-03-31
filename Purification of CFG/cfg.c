//Purification of Context-Free-Grammar.


//Importing the libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Decalring global variables/arrays.
int i,j,k,cnt=0;
char epsilon;


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
            int l=0;
            char word[10]=" ";
            for(k=0; k<strlen(pro[i].rhs[j]); k++)
            {
                if(pro[i].rhs[j][k]!=epsilon)
                {
                    word[l]=pro[i].rhs[j][k];
                    l++;
                }
            }
            strcpy(pro[i].rhs[j],word);
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
    printf("\nThe initial Grammar is :-\n\n");
    for(i=0; i<cnt; i++)
    {
        for(j=0; j<pro[i].n; j++)
        {
            printf("%s -> %s\n", pro[i].lhs, pro[i].rhs[j]);
        }
    }

    //Removal of epsilon productions.
    for(int a=0; a<cnt; a++)
    {
        for(int b=0; b<pro[a].n; b++)
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
