//Purification of Context-Free-Grammar.


//Importing the libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Decalring global variables/arrays.
int cnt=0,nullables=0;
char epsilon,nullable[10];


//Defining a structure array for productions.
struct Production
{

    char lhs[10], rhs[20][10];
    int n;

}pro[10];


//Removal of epsilon productions.
void removeEpsilon(char epsilon)
{

  int i,j,k,l;
  
    for(i=0; i<cnt; i++)
    {
        for(j=0; j<pro[i].n; j++)
        {
            int m=0,c=0;
            char word[10]="";
            for(k=0; k<strlen(pro[i].rhs[j]); k++)
            {  
                if(pro[i].rhs[j][k]==epsilon)
                {
                    c++;
                    if(c==1)
                    {
                        for(l=0;l<strlen(pro[i].rhs[j]);l++)
                        {
                            if(pro[i].rhs[j][l]!=epsilon)
                            {
                                word[m]=pro[i].rhs[j][l];
                                m++;
                            }
                        }
                    }
                }
            }
            
            if(strlen(word)!=0)
            {
                int flag=0;
                for(k=0;k<pro[i].n;k++)
                {
                    if(strcmp(pro[i].rhs[k],word)==0)
                    {
                        flag=1;
                    }
                }
                if(flag==0)
                {
                    strcpy(pro[i].rhs[pro[i].n],word);
                    pro[i].n++;
                }
            }
      
            if(c>=2)
            {
                int x,ind,y=0;
                for(x=1;x<=c;x++)
                {
                    m=0;
                    y=0;
                    for(k=0;k<strlen(pro[i].rhs[j]);k++)
                    {
                        if(pro[i].rhs[j][k]==epsilon)
                        {
                            y++;
                        }
                        if(y==x)
                        {
                            ind=k;
                            break;
                        }
                    }
                    for(l=0;l<strlen(pro[i].rhs[j]);l++)
                    {
                  
                        if(l!=ind)
                        {
                            word[m]=pro[i].rhs[j][l];
                            m++;
                        }
                    }
                    int flag=0;
                    for(k=0;k<pro[i].n;k++)
                    {
                        if(strcmp(pro[i].rhs[k],word)==0)
                        {
                            flag=1;
                        }
                    }   
                    if(flag==0)
                    {
                        strcpy(pro[i].rhs[pro[i].n],word);
                        pro[i].n++;
                    }
                }
            }
        }       
    }

}


//Finding null variables.
void findNullables()
{

    int i,j,k,l,a,b,c=0;

    for(a=0; a<cnt; a++)
    {
        for(b=0; b<pro[a].n; b++)
        {
            c=0;
            for(l=0;l<strlen(pro[a].rhs[b]);l++)
            {
                for(i=0;i<nullables;i++)
                {
                    if(nullable[i]==pro[a].rhs[b][l])
                    {
                        c++;
                    }
                }
            }
            int flag=0;
            if(c==strlen(pro[a].rhs[b]))
            {
                for(i=0;i<nullables;i++)
                {
                    if(nullable[i]==pro[a].lhs[0])
                    {
                        flag=1;
                    }
                }
                if(flag==0)
                {
                    nullable[nullables]=pro[a].lhs[0];
                    nullables++;
                    removeEpsilon(pro[a].lhs[0]);
                }
            }   
        }
    }

}


//
void add(int i,int a,int b,int c)
{

    int l,m,n,flag=0,j,i_alt;

    for(j=0;j<pro[i].n;j++)
    {
        if(strlen(pro[i].rhs[j])==1 && pro[i].rhs[j][0]>='A' && pro[i].rhs[j][0]<='Z')
        {
            for(l=0;l<cnt;l++)
            {
                if(strcmp(pro[i].rhs[j],pro[l].lhs)==0)
                {
                    i_alt=l;
                }
            }
            flag=1;
        }
        else
        {
            int f=0;
            if(c==0)
            {
                for(l=0;l<pro[a].n;l++)
                {
                    if(strcmp(pro[i].rhs[j],pro[a].rhs[l])==0)
                    {
                        f=1;
                    }
                }
                if(f!=1)
                {
                    strcpy(pro[a].rhs[b],pro[i].rhs[j]);
                    c++;
                }
                else
                {
                    for(m=b;m<pro[a].n-1;m++)
                    {
                        strcpy(pro[a].rhs[m],pro[a].rhs[m+1]);
                    }
                    pro[a].n--;
                }
                
            }
            else
            {
                for(l=0;l<pro[a].n;l++)
                {
                    if(strcmp(pro[i].rhs[j],pro[a].rhs[l])==0)
                    {
                        f=1;
                    }
                }
                if(f!=1)
                {
                    strcpy(pro[a].rhs[pro[a].n],pro[i].rhs[j]);
                    pro[a].n++;
                    c++;
                }
            }
        }
    }

    if(flag==1)
    {
        add(i_alt,a,b,c);
    }
  
}


//Removal of unit produtions.
void removeUnitProduction()
{

    int i,j,a,b;

    for(a=1; a<cnt; a++)
    {  
        for(b=0; b<pro[a].n; b++)
        {
            if(strlen(pro[a].rhs[b])==1 && pro[a].rhs[b][0]>='A' && pro[a].rhs[b][0]<='Z')
            {
                for(i=0;i<cnt;i++)
                {
                    if(strcmp(pro[a].rhs[b],pro[i].lhs) == 0)
                    {
                        add(i,a,b,0);
                    }
                }
            }
        }
    }
    
    for(b=0;b<pro[0].n;b++)
    {
        if(strlen(pro[0].rhs[b])==1 && pro[0].rhs[b][0]>='A' && pro[0].rhs[b][0]<='Z')
        {
            for(i=0;i<cnt;i++)
            {
                if(strcmp(pro[0].rhs[b],pro[i].lhs) == 0)
                {
                    add(i,0,b,0);
                }
            }
        }
    }
    
}

void remove_useless(char useless)
{

    int a,b,c,i,j,flag=0;

    for(a=0;a<cnt;a++)
    {
        if(useless==pro[a].lhs[0])
        {
            flag=1;
            break;
        }
    }
    for(a=a;a<cnt-1;a++)
    {
        pro[a]=pro[a+1];
    }

    if(flag==1)
        cnt--;
        
    for(a=0;a<cnt;a++)
    {
        for(b=0;b<pro[a].n;b++)
        {
            flag=0;
            for(c=0;pro[a].rhs[b][c]!='\0';c++)
            {
                if(pro[a].rhs[b][c]==useless)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                for(i=b;i<pro[a].n-1;i++)
                {
                    strcpy(pro[a].rhs[i],pro[a].rhs[i+1]);
                }
                pro[a].n--;
            }
        }
    }

}


//Removal of useless symbols.
void removeUselessSymbols()
{

    int a,b,c,d,k=0,l=1;
    char nt_rhs[10], useless[cnt];

    nt_rhs[0]='S';
    useless[0]='\0';
    
    for(a=1;a<cnt;a++)
    {
        int flag=0;
        for(b=0;b<pro[a].n;b++)
        {
            int count=0;
            for(c=0; pro[a].rhs[b][c]!='\0'; c++)
            {
                if(pro[a].rhs[b][c]>='a' && pro[a].rhs[b][c]<='z')
                {
                    count++;
                }
            }
            if(count==strlen(pro[a].rhs[b]))
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            useless[k]=pro[a].lhs[0];
            k++;
        }
    }

    for(a=0; a<cnt; a++)
    {
        for(b=0; b<pro[a].n; b++)
        {
            for(c=0; pro[a].rhs[b][c]!='\0'; c++)
            {
                if(pro[a].rhs[b][c]>='A' && pro[a].rhs[b][c]<='Z')
                {
                    int flag=0;
                    for(d=0; nt_rhs[d]!='\0'; d++)
                    {
                        if(pro[a].rhs[b][c]==nt_rhs[d])
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag==0)
                    {
                        nt_rhs[l] = pro[a].rhs[b][c];
                        l++;
                    }
                }
            }
        }
    }

    for(a=0; a<cnt; a++)
    {
        int flag=0;
        for(b=0; b<l; b++)
        {
            if(pro[a].lhs[0]==nt_rhs[b])
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            useless[k]=pro[a].lhs[0];
            k++;
        }
    }
    for(b=0;b<l;b++)
    {
        int flag=0;
        for(a=0;a<cnt;a++)
        {
            if(pro[a].lhs[0]==nt_rhs[b])
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            useless[k]=nt_rhs[b];
            k++;
        }
    }
    
    if(k==0)
    {
        return;
    }
    for(a=0; a<k; a++)
    {
        remove_useless(useless[a]);
    }
    
    removeUselessSymbols();

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
        printf("%s -> ",pro[i].lhs);
        for(j=0; j<pro[i].n; j++)
        {
            printf(" %s ", pro[i].rhs[j]);
            if(j!=pro[i].n-1)
                printf("|");
        }
        printf("\n");
    }

    //Removal of epsilon productions.
    for(a=0; a<cnt; a++)
    {
        for(b=0; b<pro[a].n; b++)
        {
            if(pro[a].rhs[b][0]=='#')
            {
                epsilon=pro[a].lhs[0];
                nullable[nullables]=epsilon;
                nullables++;
                pro[a].n--;
                removeEpsilon(epsilon);
                
            }
        }
    }
    

    findNullables();
    
    for(a=0;a<nullables;a++)
    {
        printf("%c ",nullable[a]);
    }
    
    printf("\nThe Grammar after removing 'lambda productions' is :-\n\n");
    for(i=0; i<cnt; i++)
    {
        printf("%s -> ",pro[i].lhs);
        for(j=0; j<pro[i].n; j++)
        {
            printf(" %s ", pro[i].rhs[j]);
            if(j!=pro[i].n-1)
                printf("|");
        }
        printf("\n");
    }
    
    removeUnitProduction();
    
    printf("\nThe Grammar after removing 'Unit productions' is :-\n\n");
    for(i=0; i<cnt; i++)
    {
        printf("%s -> ",pro[i].lhs);
        for(j=0; j<pro[i].n; j++)
        {
            printf(" %s ", pro[i].rhs[j]);
            if(j!=pro[i].n-1)
                printf("|");
        }
        printf("\n");
    }
    
    removeUselessSymbols();
    
    printf("\nThe Grammar after removing 'Useless Symbols' is :-\n\n");
    for(i=0; i<cnt; i++)
    {
        printf("%s -> ",pro[i].lhs);
        for(j=0; j<pro[i].n; j++)
        {
            printf(" %s ", pro[i].rhs[j]);
            if(j!=pro[i].n-1)
                printf("|");
        }
        printf("\n");
    }

}
