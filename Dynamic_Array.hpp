#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H


template <typename T>
struct DynamicArray
{
    int capacity, k, sizeOfArray;
    T* array;
    

    DynamicArray();
    void realloc();
    int size();
    void push_back(T object);
    void pop_back();
};


#endif /* DYNAMIC_ARRAY_H */
