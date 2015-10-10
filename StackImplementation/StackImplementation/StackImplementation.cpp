// StackImplementation.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <cstdlib> 
#include <iostream>
using namespace std;

template<typename T>
class Array
{
public:
	Array(); // Конструктор 
	Array(const Array &a); // Копирование конструктора
	~Array(); // Деструктор 
	Array& operator = (const Array &a); // создаем оператор присваивания

	T& operator [] (unsigned int index); // получить елемент массива
	void Add(const T &item); // добавить елемент в конец массива

	unsigned int GetSize(); // получить размер массива
	void SetSize(unsigned int newsize); // установаить размер массива
	void Clear(); // очистить массив 
	void Delete(unsigned int pos); // удалить элемент массива
	void* getptr(); // получить указатель на массив с данными

	enum exception { MEMFAIL }; // ошибка "нехватка памяти"

private:
	T *array; // указатель на массив в памяти
	unsigned int size; // размер массива (элемент) 
	unsigned int realsize; // актуальный размер выделенной памяти

	const static int dyn_array_step = 100; // начальное количество памяти под массив
	const static int dyn_array_mult = 2; // во сколько раз увеличить размер массива

};


template <typename T>
Array<T>::Array()
{
	realsize = dyn_array_step; // выделение памяти под массив
	size = 0;
	array = (T *)malloc(realsize*sizeof(T)); // создаем массив с указателем на 1й елемент

	if (array == NULL)					// проверяем создан ли массив
		throw MEMFAIL;
}

template <typename T>
Array<T>::~Array()
{
	if (array)
	{
		free(array); // Освобождение памяти
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
	// копирование одного масива в другой 
	realsize = a.realsize;
	size = a.size;
}

template <typename T>
Array<T>& Array<T>::operator = (const Array &a)
{
	if (this == &a) // проверка не указывает ли массив на себя
		return *this;

	if (a.size == 0) // если другйо массив пустой - очистить этот массив
		Clear();

	SetSize(a.size); // установить размер

	memcpy(array, a.array, sizeof(T)*a.size);

	return *this;
}

template <typename T>
unsigned int Array<T>::GetSize()
{
	return size; // возвращение размера
}


template <typename T>
void Array<T>::SetSize(unsigned int newsize)
{
	size = newsize;

	if (size != 0)
	{
		// Корректировка размера массива
		// если новый размер массива больше чем текущий
		// или новый размер меньше то уменьшаем в двое текущий размер массива
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
	if (size == 1) // Если массив имеет только один елемент
		Clear(); // то мы очищаем массив
	else
	{
		// иначе смещаем
		for (unsigned int i = pos; i < size - 1; i++)
			array[i] = array[i + 1];

		// уменьшаем размер массива
		size--;
	}
}

template <typename T>
void Array<T>::Clear() // очищаем память массива 
{
	size = 0;
	array = (T *)realloc(array, sizeof(T)*dyn_array_step);
	// инициализируем память под массив снова
	realsize = dyn_array_step;
}

template <typename T>
void* Array<T>::getptr()
{
	return array; // возвращаем указатель
}

template <typename T>
T& Array<T>::operator [] (unsigned int index)
{
	return array[index]; // возвращаем элемент
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

// вывод эелементов массива
void output_array(Array<int> &array)
{
	for (unsigned int i = 0; i < array.GetSize(); i++)
		cout << array[i] << ", ";

	cout << endl;
}

int main(void)
{
	Array<int> array;

	array.SetSize(3); // указываем размер массива

					  // добавляем элементы в массив
	array.Add(7);
	array.Add(94);
	array.Add(1);

	// выводим их
	output_array(array);

	// удаляем первый элемент массива
	array.Delete(0);
	array.Delete(array.GetSize() - 1);

	// снова выводим элементы массива 
	output_array(array);

	// создаем другой массив с=основанный на первом
	Array<int> array2(array);
	array2.Clear(); // очищаем

					// проверяем присваивание
	array = array2;

	// вывод массива
	cout << "array 2 size " << array2.GetSize() << endl;
	cout << "array 1 size " << array.GetSize() << endl;
	return 0;
}