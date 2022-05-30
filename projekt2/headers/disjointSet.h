#pragma once
#define DEFAULT_SIZE 10

template <typename T>
struct Elem
{
    T *value;
    int parent;
    int index;
    int rank;
};

template <typename T>
class DisjointSet
{
private:
    Elem<T> **arr;
    int size;
    int current_size;

public:
    DisjointSet();
    DisjointSet(int size);
    ~DisjointSet();
    Elem<T> *makeSet(T *value);
    void unionSets(Elem<T> &elem_one, Elem<T> &elem_two);
    void link(Elem<T> &elem_one, Elem<T> &elem_two);
    Elem<T> *findSet(Elem<T> &elem);
    void print();
};

#include "../src/disjointSet.cpp"
