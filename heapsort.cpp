#include "heapsort.h"

template <typename T>
void Heapsort::sink(T *&array, int parent_index, int start, int end)
{

    int child_index = 2 * parent_index + 1 - start;
    if (child_index <= end)
    {
        if (child_index + 1 <= end && array[child_index] < array[child_index + 1])
        {
            child_index++;
        }
        if (array[child_index] > array[parent_index])
        {
            std::swap(array[parent_index], array[child_index]);
            sink(array, child_index, start, end);
        }
    }
}

template <typename T>
void Heapsort::heap_adjustment(T *&array, int start, int end) // uklada tablice w kopiec
{
    for (int index = (start + end) / 2; index >= start; --index)
    {
        sink(array, index, start, end);
    }
}

template <typename T>
void Heapsort::heap_sort(T *&array, int start, int end)
{
    heap_adjustment(array, start, end);

    for (int index = end; index > start; --index)
    {
        std::swap(array[start], array[index]);
        sink(array, start, start, index - 1);
    }
}
