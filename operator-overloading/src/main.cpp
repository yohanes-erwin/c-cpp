#include <iostream>

using namespace std;

class Time
{
private:
	int hours;
	int minutes;

public:
	Time()
	{
		hours = 0;
		minutes = 0;
	}

	Time(int h, int m)
	{
		hours = h;
		minutes = m;
	}

	Time operator+(const Time &t) const
	{
		Time sum;
		sum.minutes = minutes + t.minutes;
		sum.minutes %= 60;
		sum.hours = hours + t.hours + sum.minutes/60;

		return sum;
	}

	void Show() const
	{
		cout << hours << " hours, " << minutes << " minutes.\n";
	}
};

int main()
{
	Time a(1, 30);
	Time b(2, 15);
	Time c;

	c = a + b;

	a.Show();
	b.Show();
	c.Show();

	return 0;
}
