// StackImplementation.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "stdafx.h"
#include <cstdlib> 
#include <iostream>
using namespace std;

template<typename T>
class Array
{
public:
	Array(); // ����������� 
	Array(const Array &a); // ����������� ������������
	~Array(); // ���������� 
	Array& operator = (const Array &a); // ������� �������� ������������

	T& operator [] (unsigned int index); // �������� ������� �������
	void Add(const T &item); // �������� ������� � ����� �������

	unsigned int GetSize(); // �������� ������ �������
	void SetSize(unsigned int newsize); // ����������� ������ �������
	void Clear(); // �������� ������ 
	void Delete(unsigned int pos); // ������� ������� �������
	void* getptr(); // �������� ��������� �� ������ � �������

	enum exception { MEMFAIL }; // ������ "�������� ������"

private:
	T *array; // ��������� �� ������ � ������
	unsigned int size; // ������ ������� (�������) 
	unsigned int realsize; // ���������� ������ ���������� ������

	const static int dyn_array_step = 100; // ��������� ���������� ������ ��� ������
	const static int dyn_array_mult = 2; // �� ������� ��� ��������� ������ �������

};


template <typename T>
Array<T>::Array()
{
	realsize = dyn_array_step; // ��������� ������ ��� ������
	size = 0;
	array = (T *)malloc(realsize*sizeof(T)); // ������� ������ � ���������� �� 1� �������

	if (array == NULL)					// ��������� ������ �� ������
		throw MEMFAIL;
}

template <typename T>
Array<T>::~Array()
{
	if (array)
	{
		free(array); // ������������ ������
		array = NULL;
	}
}

template <typename T>
Array<T>::Array(const Array &a)
{
	array = (T *)malloc(sizeof(T)*a.realsize);
	if (array == NULL)
		throw MEMFAIL;

	memcpy(array, a.array, sizeof(T)*a.realsize);
	// ����������� ������ ������ � ������ 
	realsize = a.realsize;
	size = a.size;
}

template <typename T>
Array<T>& Array<T>::operator = (const Array &a)
{
	if (this == &a) // �������� �� ��������� �� ������ �� ����
		return *this;

	if (a.size == 0) // ���� ������ ������ ������ - �������� ���� ������
		Clear();

	SetSize(a.size); // ���������� ������

	memcpy(array, a.array, sizeof(T)*a.size);

	return *this;
}

template <typename T>
unsigned int Array<T>::GetSize()
{
	return size; // ����������� �������
}


template <typename T>
void Array<T>::SetSize(unsigned int newsize)
{
	size = newsize;

	if (size != 0)
	{
		// ������������� ������� �������
		// ���� ����� ������ ������� ������ ��� �������
		// ��� ����� ������ ������ �� ��������� � ���� ������� ������ �������
		if ((size > realsize) || (size < realsize / 2))
		{
			realsize = size;
			array = (T *)realloc(array, sizeof(T)*size);

			if (array == NULL)
				throw MEMFAIL;
		}
	}
	else
		Clear();
}

template <typename T>
void Array<T>::Delete(unsigned int pos)
{
	if (size == 1) // ���� ������ ����� ������ ���� �������
		Clear(); // �� �� ������� ������
	else
	{
		// ����� �������
		for (unsigned int i = pos; i < size - 1; i++)
			array[i] = array[i + 1];

		// ��������� ������ �������
		size--;
	}
}

template <typename T>
void Array<T>::Clear() // ������� ������ ������� 
{
	size = 0;
	array = (T *)realloc(array, sizeof(T)*dyn_array_step);
	// �������������� ������ ��� ������ �����
	realsize = dyn_array_step;
}

template <typename T>
void* Array<T>::getptr()
{
	return array; // ���������� ���������
}

template <typename T>
T& Array<T>::operator [] (unsigned int index)
{
	return array[index]; // ���������� �������
}

template <typename T>
void Array<T>::Add(const T &item)
{
	size++;

	if (size > realsize)
	{
		realsize *= dyn_array_mult;

		array = (T *)realloc(array, sizeof(T)*realsize);

		if (array == NULL)
			throw MEMFAIL;
	}

	array[size - 1] = item;
}

// ����� ���������� �������
void output_array(Array<int> &array)
{
	for (unsigned int i = 0; i < array.GetSize(); i++)
		cout << array[i] << ", ";

	cout << endl;
}

int main(void)
{
	Array<int> array;

	array.SetSize(3); // ��������� ������ �������

					  // ��������� �������� � ������
	array.Add(7);
	array.Add(94);
	array.Add(1);

	// ������� ��
	output_array(array);

	// ������� ������ ������� �������
	array.Delete(0);
	array.Delete(array.GetSize() - 1);

	// ����� ������� �������� ������� 
	output_array(array);

	// ������� ������ ������ �=���������� �� ������
	Array<int> array2(array);
	array2.Clear(); // �������

					// ��������� ������������
	array = array2;

	// ����� �������
	cout << "array 2 size " << array2.GetSize() << endl;
	cout << "array 1 size " << array.GetSize() << endl;
	return 0;
}