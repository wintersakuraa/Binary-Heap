#include "Dynamic_Array.hpp"
#include <iostream>


using namespace std;


template <typename T>
DynamicArray<T>::DynamicArray()
{
    capacity = 1;
    k = 2;
    sizeOfArray = 0;
    array = new T[capacity];
}


template <typename T>
void DynamicArray<T>::realloc()
{
    capacity *= k;
    T* newArray = new T[capacity];
    
    for (int i = 0; i < sizeOfArray; i++)
    {
        newArray[i] = array[i];
    }
    
    delete[] array;
    array = newArray;
}


template <typename T>
int DynamicArray<T>::size()
{
    return sizeOfArray;
}


template <typename T>
void DynamicArray<T>::push_back(T object)
{
    if(sizeOfArray == capacity)
    {
        realloc();
    }
    
    array[sizeOfArray++] = object;
}


template <typename T>
void DynamicArray<T>::pop_back()
{
    if (sizeOfArray)
    {
        sizeOfArray--;
    }
    else
    {
        cout << "ERROR: ARRAY IS EMPTY" << endl;
    }
}
