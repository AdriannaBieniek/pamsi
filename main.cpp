#include <iostream>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <iomanip>
#include "merging.h"
#include "quick.h"
#include "introspective.h"
#include "heapsort.h"
#include "randomarray.h"

#define AMOUNT_OF_ARRAYS 100
#define SIZE_OF_RESULTS 3
#define AMOUNT_OF_RESULTS_ONE_LINE 8

using namespace std;

template <typename T>
bool check_if_same(T *&array_to_check, T *&sorted_array, int size)
{
    for (int array_index = 0; array_index < AMOUNT_OF_ARRAYS; ++array_index)
    {
        for (int index = 0; index < size; ++index)
        {
            if (array_to_check[array_index][index] != sorted_array[array_index][index])
                return false;
        }
    }

    return true;
}

template <typename T>
double measure_sort(T **&array_of_arrays, T **&array_of_sorted, int size, char option_sort)
{

    double durationSum = 0;

    chrono::steady_clock::time_point beginTime;
    chrono::steady_clock::time_point endTime;

    for (int array_index = 0; array_index < AMOUNT_OF_ARRAYS; ++array_index)
    {

        // for (int index = 0; index < size; ++index)
        // {
        //     cout << array_of_arrays[array_index][index] << " ";
        // }
        // cout << "\n";

        switch (option_sort)
        {
        case 'm':
            beginTime = chrono::steady_clock::now();
            Merging::merge_sort(array_of_arrays[array_index], 0, size - 1);
            endTime = chrono::steady_clock::now();
            break;
        case 'q':
            beginTime = chrono::steady_clock::now();
            Quicksort::quick_sort(array_of_arrays[array_index], 0, size - 1);
            endTime = chrono::steady_clock::now();
            break;
        case 'i':
            beginTime = chrono::steady_clock::now();
            Introspective::introspective_sort(array_of_arrays[array_index], 0, size - 1, 2 * log2(size));
            endTime = chrono::steady_clock::now();
            break;
        default:
            return 0;
            break;
        }

        durationSum += chrono::duration_cast<chrono::nanoseconds>(endTime - beginTime).count();
        // for (int index = 0; index < size; ++index)
        // {
        //     cout << array_of_arrays[array_index][index] << " ";
        // }
        // cout << "\n";
    }
    // cout << check_if_same(array_of_arrays, array_of_sorted, size) << " ";

    return durationSum / AMOUNT_OF_ARRAYS;
}

template <typename T>
void create_set_arr_and_measure(double **&results, int index_of_result, int size, double option_sorted)
{
    T **array_of_arrays_merge = new T *[AMOUNT_OF_ARRAYS];
    T **array_of_arrays_quick = new T *[AMOUNT_OF_ARRAYS];
    T **array_of_arrays_intro = new T *[AMOUNT_OF_ARRAYS];
    T **array_of_sorted = new T *[AMOUNT_OF_ARRAYS];

    for (int array_index = 0; array_index < AMOUNT_OF_ARRAYS; ++array_index)

    {
        array_of_arrays_merge[array_index] = new T[size];
        array_of_arrays_quick[array_index] = new T[size];
        array_of_arrays_intro[array_index] = new T[size];
        array_of_sorted[array_index] = new T[size];

        Randomarray::make_random_array(array_of_arrays_merge[array_index], size, option_sorted);

        for (int index = 0; index < size; ++index)
        {
            array_of_sorted[array_index][index] = array_of_arrays_merge[array_index][index];
            array_of_arrays_quick[array_index][index] = array_of_arrays_merge[array_index][index];
            array_of_arrays_intro[array_index][index] = array_of_arrays_merge[array_index][index];
        }

        sort(array_of_sorted[array_index], array_of_sorted[array_index] + size);
    }

    results[0][index_of_result] = measure_sort<T>(array_of_arrays_merge, array_of_sorted, size, 'm');
    if (index_of_result != 8)
        results[1][index_of_result] = measure_sort<T>(array_of_arrays_quick, array_of_sorted, size, 'q');
    else
        results[1][index_of_result] = 0;
    results[2][index_of_result] = measure_sort<T>(array_of_arrays_intro, array_of_sorted, size, 'i');

    // cout << "\n";

    for (int index = 0; index < AMOUNT_OF_ARRAYS; ++index)
    {
        delete[] array_of_arrays_merge[index];
        delete[] array_of_arrays_quick[index];
        delete[] array_of_arrays_intro[index];
        delete[] array_of_sorted[index];
    }

    delete[] array_of_arrays_merge;
    delete[] array_of_arrays_quick;
    delete[] array_of_arrays_intro;
    delete[] array_of_sorted;
}

int main(int argc, char const *argv[])
{

    srand(time(NULL));

    double **results = new double *[SIZE_OF_RESULTS];

    for (int index = 0; index < SIZE_OF_RESULTS; ++index)
    {
        results[index] = new double[AMOUNT_OF_RESULTS_ONE_LINE];
    }

    int sizes[5] = {10000, 50000, 100000, 500000, 1000000};
    double types_of_data[8] = {0, 25, 50, 75, 95, 99, 99.7, -1};

    printf("Name\t\t\t\t0\t\t25\t\t50\t\t75\t\t95\t\t99\t\t99.7\t\treversed\n");

    for (int index = 0; index < sizeof(sizes) / sizeof(*sizes); ++index)
    {
        for (int index_data = 0; index_data < sizeof(types_of_data) / sizeof(*types_of_data); ++index_data)
        {
            create_set_arr_and_measure<int>(results, index_data, sizes[index], types_of_data[index_data]);
        }
        printf("Dla rozmiaru %d:\n", sizes[index]);
        printf("Merge sort:\t\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f ns\n", results[0][0], results[0][1], results[0][2], results[0][3], results[0][4], results[0][5], results[0][6], results[0][7]);
        printf("Quick sort:\t\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f ns\n", results[1][0], results[1][1], results[1][2], results[1][3], results[1][4], results[1][5], results[1][6], results[1][7]);
        printf("Intro sort:\t\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f ns\n", results[2][0], results[2][1], results[2][2], results[2][3], results[2][4], results[2][5], results[2][6], results[2][7]);

        cout << "--------------------------------------\n";
    }

    for (int index = 0; index < SIZE_OF_RESULTS; ++index)
    {
        delete[] results[index];
    }

    delete[] results;

    return 0;
}
