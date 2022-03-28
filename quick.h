#pragma once
namespace Quicksort
{

    template <typename T>
    void quick_sort(T *&array, int start, int end);
    template <typename T>
    int find_pivot(T *&array, int start, int end);
    template <typename T>
    int partition(T *&array, int start, int end);

}
#include "quick.cpp"
