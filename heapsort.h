#pragma once
namespace Heapsort
{

    template <typename T>
    void sink(T *&array, int parent_index, int start, int end);
    template <typename T>
    void heap_adjustment(T *&array, int start, int end);
    template <typename T>
    void heap_sort(T *&array, int start, int end);
}
#include "heapsort.cpp"
