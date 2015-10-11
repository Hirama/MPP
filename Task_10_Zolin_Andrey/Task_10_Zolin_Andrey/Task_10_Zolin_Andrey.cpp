// Task_10_Zolin_Andrey.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

template <int leftBorder, int rightBorder>
class Range
{
	int value;		// the single member!
	Range() {}		// private default constructor
public:
	Range(int v)
	{
		assert(leftBorder <= rightBorder);
		value = v;
		check();
	}

	Range(Range &r)
	{
		value = r.value;
	}

	~Range()
	{
		value = leftBorder;
	}

	Range& operator= (Range &r)
	{
		value = r.value;
		return *this;
	}

	Range& operator++ ()
	{
		value++;
		check();
		return *this;
	}

	Range& operator-- ()
	{
		value--;
		check();
		return *this;
	}

	Range operator+ (int add)
	{
		Range r(value + add);
		check();
		return r;
	}

	Range& operator- (int sub)
	{
		value -= sub;
		check();
		return *this;
	}

	Range& operator+= (int add)
	{
		value += add;
		check();
		return *this;
	}

	Range& operator-= (int sub)
	{
		value -= sub;
		check();
		return *this;
	}

	bool operator< (Range &r)
	{
		return value < r.value;
	}

	bool operator> (Range &r)
	{
		return value > r.value;
	}

	bool operator== (Range &r)
	{
		return value == r.value;
	}

	bool operator!= (Range &r)
	{
		return value != r.value;
	}

	operator long()
	{
		return value;
	}

	void check()
	{
		if (value < leftBorder || value > rightBorder)
		{
			throw OUT_OF_RANGE;
		}
	}

	static const int OUT_OF_RANGE = 1;
};

bool isPrime(long num)
{
	for (long i = 2; i <= sqrt(num); ++i)
	{
		if (num % i == 0) return false;
	}
	return true;
}

int main()
{
	Range<2, 100> rangePrime(2);
	try
	{
		do
		{
			cout << rangePrime << (isPrime(rangePrime) ? " is prime" : " is not prime") << endl;
		} while (++rangePrime);
	}
	catch (int i)
	{
		if (i == rangePrime.OUT_OF_RANGE)
		{
			cout << "end of loop" << endl;
		}
	}

	Range <0, 20> range20(0);
	cout << range20 << endl;
	range20 + 5;
	cout << range20 << endl;
	range20 += 5;
	cout << range20 << endl;

	// range20 += 45;   		exception!
	// range20 = rangePrime;	compilation error
	cout << (range20 < rangePrime) << endl;		// OK
	Range<0, 20> range20_2(1);
	range20_2 = range20;
	cout << (range20 == range20_2) << endl;

	return 0;
}