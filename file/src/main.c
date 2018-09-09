#include <stdio.h>

int main()
{
	// *** Open file ***
	char *file_name = "D:\\Microelectronics\\Eclipse\\cpp\\file\\src\\text.txt";
	FILE *file_p = fopen(file_name, "r");
	if (file_p == NULL)
	{
		printf("Could not open file %s\n", "text.txt");
		return 1;
	}

	// *** Print text ***
	while (1)
	{
		char c = fgetc(file_p);
		if (feof(file_p))
			break;
		printf("%c", c);
	}

	// *** Close file ***
	fclose(file_p);

	return 0;
}
