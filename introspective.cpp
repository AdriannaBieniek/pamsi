#include "introspective.h"
#include "quick.h"
#include "heapsort.h"

template <typename T>
void Introspective::introspective_sort(T *&array, int start, int end, int depth)
{

    if (end == start)
        return;

    if (start < end)
    {
        if (depth <= 0)
        {
            Heapsort::heap_sort(array, start, end);
            return;
        }
        int pivot = Quicksort::partition(array, start, end); // zwraca indeks pivota w dobrej pozycji
        if (pivot > start)
            introspective_sort(array, start, pivot - 1, depth - 1);
        if (pivot < end)
            introspective_sort(array, pivot + 1, end, depth - 1);
    }
}
