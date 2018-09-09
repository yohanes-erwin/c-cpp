#include <iostream>

using namespace std;

int x = 1, y = 1;
double m = 2.0, n = 2.0;

template<typename T>
T sum(T a, T b);

int main()
{
	cout << sum<int>(x, y) << '\n';
	cout << sum<double>(m, n) << '\n';

	return 0;
}

template<typename T>
T sum(T a, T b)
{
	return (a + b);
}
