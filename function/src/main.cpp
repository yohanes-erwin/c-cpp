#include <iostream>

using namespace std;

int index;

void passByValue(int n);
void passByReference(int &n);
void passByPointer(int *n);

int main()
{
	index = 1;
	cout << "Index = " << index << '\n';
	passByValue(index);
	cout << "Index after passByValue() = " << index << '\n';

	index = 1;
	cout << "Index = " << index << '\n';
	passByReference(index);
	cout << "Index after passByReference() = " << index << '\n';

	index = 1;
	cout << "Index = " << index << '\n';
	passByPointer(&index);
	cout << "Index after passByPointer() = " << index << '\n';

	return 0;
}

void passByValue(int n)
{
	++n;
}

void passByReference(int &n)
{
	++n;
}

void passByPointer(int *n)
{
	++(*n);
}
