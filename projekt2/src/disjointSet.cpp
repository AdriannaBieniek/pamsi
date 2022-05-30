#include "../headers/disjointSet.h"

template <typename T>
DisjointSet<T>::DisjointSet()
{
    this->size = DEFAULT_SIZE;
    this->current_size = 0;
    this->arr = new Elem<T> *[this->size];
}

template <typename T>
DisjointSet<T>::DisjointSet(int size)
{
    this->size = size;
    this->current_size = 0;
    this->arr = new Elem<T> *[this->size];
}

template <typename T>
DisjointSet<T>::~DisjointSet()
{
    delete[] this->arr;
}

template <typename T>
Elem<T> *DisjointSet<T>::makeSet(T *value)
{
    if (this->current_size == this->size)
        return nullptr;

    this->arr[this->current_size] = new Elem<T>{value, this->current_size, this->current_size, 0}; // value, parent, index, rank
    this->current_size++;
    return this->arr[this->current_size - 1];
}

template <typename T>
Elem<T> *DisjointSet<T>::findSet(Elem<T> &elem)
{
    if (elem.index != elem.parent)
        elem.parent = this->findSet(*this->arr[elem.parent])->index;

    return this->arr[elem.parent];
}

template <typename T>
void DisjointSet<T>::link(Elem<T> &elem_one, Elem<T> &elem_two)
{
    if (elem_one.rank > elem_two.rank)
        elem_two.parent = elem_one.index;
    else
    {
        elem_one.parent = elem_two.index;
        if (elem_one.rank == elem_two.rank)
            elem_two.rank += 1;
    }
}

template <typename T>
void DisjointSet<T>::unionSets(Elem<T> &elem_one, Elem<T> &elem_two)
{
    this->link(*this->findSet(elem_one), *this->findSet(elem_two));
}

template <typename T>
void DisjointSet<T>::print()
{
    for (int index = 0; index < current_size; ++index)
    {
        std::cout << *this->arr[index]->value << ":" << this->arr[index]->parent << ":" << this->arr[index]->index << ":" << this->arr[index]->rank << " ";
    }
    std::cout << "\n";
}
