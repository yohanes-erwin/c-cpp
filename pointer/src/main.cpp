#include <iostream>

using namespace std;

int numbers[5];
int *pointer;

int main()
{
	// Get address 0
	pointer = numbers;
	cout << pointer << '\n';
	pointer = &numbers[0];
	cout << pointer << '\n';

	// Input element 0
	pointer = numbers;
	*pointer = 10;

	// Input element 1
	pointer = &numbers[1];
	*pointer = 20;

	// Input element 2
	pointer = numbers + 2;
	*pointer = 30;

	// Input element 3
	pointer++;
	*pointer = 40;

	// Input element 4
	pointer = numbers;
	*(pointer+4) = 50;

	// Print array
	for (int i = 0; i < 5; i++)
	{
		cout << numbers[i] << '\n';
	}

	// Same as *(p++):
	// Increment pointer and deference unincremented address
	pointer = numbers;
	cout << *pointer++ << '\n';
	// Same as *(++p):
	// Increment pointer and deference incremented address
	pointer = numbers;
	cout << *++pointer << '\n';
	// Same as ++(*p):
	// Deference pointer and increment the value it points to
	pointer = numbers;
	cout << ++*pointer << '\n';
	// Deference pointer and post-increment the value it points to
	pointer = numbers;
	cout << (*pointer)++ << '\n';

	return 0;
}
