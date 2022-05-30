#include "../headers/priorityQueueMin.h"

template <typename T>
PriorityQueueMin<T>::PriorityQueueMin()
{
    this->size = DEFAULT_SIZE;
    this->currentSize = 0;
    this->arr = new T[this->size];
}

template <typename T>
PriorityQueueMin<T>::PriorityQueueMin(int size)
{
    this->size = size;
    this->currentSize = 0;
    this->arr = new T[size];
}

template <typename T>
PriorityQueueMin<T>::~PriorityQueueMin()
{
    delete[] this->arr;
}

template <typename T>
void PriorityQueueMin<T>::enqueue(T &newElement)
{
    if (this->currentSize == this->size)
        return;

    this->arr[this->currentSize] = newElement;
    this->currentSize++;
    this->swim(this->currentSize - 1);
}

template <typename T>
T PriorityQueueMin<T>::removeMin()
{
    T min_elem = this->arr[0];
    std::swap(this->arr[0], this->arr[this->currentSize - 1]);
    this->currentSize--;
    this->sink(0);

    return min_elem;
}

template <typename T>
void PriorityQueueMin<T>::sink(int index)
{

    int child = 2 * index + 1;
    if (child < this->currentSize)
    {
        if (child + 1 < this->currentSize && this->arr[child + 1] < this->arr[child])
            child++;

        if (this->arr[index] > this->arr[child])
        {
            std::swap(this->arr[index], this->arr[child]);
            sink(child);
        }
    }
}

template <typename T>
void PriorityQueueMin<T>::swim(int index)
{
    if (index == 0 || index >= this->currentSize)
        return;
    int parent = (index - 1) / 2;

    if (this->arr[parent] > this->arr[index])
    {

        std::swap(this->arr[index], this->arr[parent]);
        swim(parent);
    }
}

template <typename T>
void PriorityQueueMin<T>::print()
{
    for (int index = 0; index < this->currentSize; ++index)
    {

        std::cout << this->arr[index] << " ";
    }
    std::cout << "\n";
}

template <typename T>
bool PriorityQueueMin<T>::isEmpty()
{
    return currentSize == 0;
}

template <typename T>
bool PriorityQueueMin<T>::doesContain(T &elem)
{
    for (int index = 0; index < this->currentSize; ++index)
    {
        if (this->arr[index] == elem)
            return true;
    }
    return false;
}
