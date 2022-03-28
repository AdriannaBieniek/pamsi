#include "quick.h"
#include <algorithm>
template <typename T>
int Quicksort::find_pivot(T *&array, int start, int end) // zwraca mediane ze skrajnych i srodkowego elementu
{
    // int middle = ((start + end) / 2);

    // if (array[middle] < array[start])
    //     std::swap(array[middle], array[start]);

    // if (array[end] < array[start])
    //     std::swap(array[end], array[start]);

    // if (array[middle] < array[end])
    //     std::swap(array[middle], array[end]);

    return end;
}

template <typename T>
void Quicksort::quick_sort(T *&array, int start, int end)
{
    if (end == start)
        return;

    if (start < end)
    {
        int pivot = partition(array, start, end); // zwraca indeks pivota w dobrej pozycji
        if (pivot > start)
            quick_sort(array, start, pivot - 1);
        if (pivot < end)
            quick_sort(array, pivot + 1, end);
    }
}

template <typename T>
int Quicksort::partition(T *&array, int start, int end)
{
    int pivot = find_pivot(array, start, end);
    T pivot_value = array[pivot];

    std::swap(array[start], array[pivot]);

    int higher_index = start + 1;
    int lower_index = end;

    do
    {
        while (higher_index <= lower_index && array[higher_index] <= pivot_value)
            higher_index++;

        while (array[lower_index] > pivot_value)
            lower_index--;

        if (higher_index < lower_index)
            std::swap(array[higher_index], array[lower_index]);

    } while (higher_index < lower_index);

    std::swap(array[start], array[lower_index]);

    return lower_index;
}
