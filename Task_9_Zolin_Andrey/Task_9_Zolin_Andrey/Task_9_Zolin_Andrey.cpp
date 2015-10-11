// Task_9_Zolin_Andrey.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
class CompareLess
{
public:
	bool less(const T &v1, const T &v2)
	{
		cout << "comparing arbitrary objects" << endl;
		return v1 < v2;
	}
};

template <>
class CompareLess<const char*>
{
public:
	bool less(const char *v1, const char *v2)
	{
		cout << "comparing const char*" << endl;
		return strcmp(v1, v2) < 0;
	}
};

template <typename T>
class CompareLess <T*>
{
public:
	bool less(T *v1, T *v2)
	{
		cout << "comparing pointers" << endl;
		return *v1 < *v2;
	}
};

int main()
{
	CompareLess<int> compInt;
	cout << compInt.less(5, 1) << endl;
	cout << compInt.less(-2, 7) << endl;
	CompareLess<double*> compFloating;
	double d1 = 8.12, d2 = 1.76;
	cout << compFloating.less(&d1, &d2) << endl;
	cout << compFloating.less(&d2, &d1) << endl;
	const char *str1 = "organization";
	const char *str2 = "book";
	CompareLess<const char*> compString;
	cout << compString.less(str1, str2) << endl;
	return 0;
}