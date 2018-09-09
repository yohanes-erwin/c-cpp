#include <iostream>

using namespace std;

int n;
int *m;

int main()
{
	cout << "How many numbers would you like to type? ";
	cin >> n;
	m = new int[n];

	for (int i = 0; i < n; i++)
	{
		cout << "Enter number: ";
		cin >> m[i];
	}

	cout << "You have entered:\n";
	for (int i = 0; i < n; i++)
	{
		cout << m[i] << '\n';
	}

	delete[] m;

	return 0;
}
