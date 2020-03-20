//Checking if a number is divisible by 3 or not.

int main()
{

	//Declaring the variables/arrays.
	int number,state=0,i=0,j;
	int digit[16];

	//Taking input.
	printf("Enter the number :- ");
	scanf("%d",&number);
	
	//Converting a decimal number to binary.
	while(number>0)
	{
		digit[i]=number%2;
		number/=2;
		i++;
	}

	//Checking each digit.
	for(j=i-1; j>=0; j--)
	{
		if(state==0)
		{
			if(digit[j]==1)
				state=1;
		}
		else if(state==1)
		{
			if(digit[j]==0)
				state=2;
			else
				state=0;
		}
		else if(state==2)
		{
			if(digit[j]==0)
				state=1;
		}
	}

	//Checking the final-state.
	if(state==0)
		printf("Accepted\n");
	else
		printf("Rejected\n");

}
