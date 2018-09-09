#include <iostream>

using namespace std;

int x = 1, y = 1;
double m = 2.0, n = 2.0;

int sum(int a, int b);
double sum(double a, double b);

int main()
{
	cout << sum(x, y) << '\n';
	cout << sum(m, n) << '\n';

	return 0;
}

int sum(int a, int b)
{
	return (a + b);
}

double sum(double a, double b)
{
	return (a + b);
}
