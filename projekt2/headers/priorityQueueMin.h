#pragma once
#define DEFAULT_SIZE 10

template <typename T>
class PriorityQueueMin
{
private:
    int size;
    int currentSize;
    T *arr;
    void sink(int index);
    void swim(int index);

public:
    PriorityQueueMin();
    PriorityQueueMin(int size);
    ~PriorityQueueMin();
    void enqueue(T &new_element);
    T removeMin();
    void print();
    bool isEmpty();
    bool doesContain(T &elem);
};

#include "../src/priorityQueueMin.cpp"
