#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("The argument supplied is %s\n", argv[1]);
	}
	else if (argc > 2)
	{
		printf("Error: Too many arguments supplied.\n");
	}
	else
	{
		printf("Error: One argument expected.\n");
	}
}
