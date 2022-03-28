#include "randomarray.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

void Randomarray::make_random_array(double *&array, int size, double amount_to_sort)
{
    int size_of_sorted;
    if (amount_to_sort >= 0)
        size_of_sorted = (int)(size * amount_to_sort / 100);
    else
        size_of_sorted = 0;

    for (int index = 0; index < size; ++index)
    {
        if (index < size_of_sorted)
            array[index] = index;
        else
            array[index] = ((double)rand() / RAND_MAX) * (size - size_of_sorted);
    }

    if (amount_to_sort == -1)
        std::sort(array, array + size, std::greater<double>());
}

void Randomarray::make_random_array(char *&array, int size, double amount_to_sort)
{
    int size_of_sorted;
    if (amount_to_sort >= 0)
        size_of_sorted = (int)(size * amount_to_sort / 100);
    else
        size_of_sorted = 0;

    for (int index = 0; index < size; ++index)
    {
        if (index < size_of_sorted)
            array[index] = 'a';
        else
            array[index] = 'b' + rand() % 25;
    }

    if (amount_to_sort == -1)
        std::sort(array, array + size, std::greater<char>());
}

void Randomarray::make_random_array(int *&array, int size, double amount_to_sort)
{
    int size_of_sorted;
    if (amount_to_sort >= 0)
        size_of_sorted = (int)(size * amount_to_sort / 100);
    else
        size_of_sorted = 0;

    for (int index = 0; index < size; ++index)
    {

        if (index < size_of_sorted)
            array[index] = index;
        else
            array[index] = rand() % size + size_of_sorted;
    }

    if (amount_to_sort == -1)
        std::sort(array, array + size, std::greater<int>());
}