#include <iostream>

using namespace std;

int x = 1, y = 1;
double m = 2.0, n = 2.0;

template<typename T>
T sum(T a, T b);
template<typename T>
T sum(T a, T b, T c);

int main()
{
	cout << sum<int>(x, y) << '\n';
	cout << sum<int>(x, y, 1) << '\n';
	cout << sum<double>(m, n) << '\n';
	cout << sum<double>(m, n, 2.0) << '\n';

	return 0;
}

template<typename T>
T sum(T a, T b)
{
	return (a + b);
}

template<typename T>
T sum(T a, T b, T c)
{
	return (a + b + c);
}
