#include "merging.h"

template <typename T>
void Merging::merging(T *&array, int start, int middle, int end)
{

    int left_array = start, right_array = middle + 1;
    int size = end + 1 - start;
    T *temp_array = new T[size];
    for (int index = 0; index < size; ++index)
    {
        if (right_array == end + 1 || (left_array < middle + 1 && array[left_array] <= array[right_array]))
        {
            temp_array[index] = array[left_array];
            left_array++;
        }
        else if (left_array == middle + 1 || (right_array < end + 1 && array[right_array] < array[left_array]))
        {
            temp_array[index] = array[right_array];
            right_array++;
        }
    }

    int temp_index = 0;
    for (int index = start; index <= end; ++index)
    {
        array[index] = temp_array[temp_index];
        temp_index++;
    }

    delete[] temp_array;
}

template <typename T>
void Merging::merge_sort(T *&array, int start, int end) // przedzialu
{
    if (end - start > 0)
    {
        int middle = (start + end) / 2;

        merge_sort<T>(array, start, middle);
        merge_sort<T>(array, middle + 1, end);
        merging<T>(array, start, middle, end);
    }
}
