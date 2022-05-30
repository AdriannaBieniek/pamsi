#pragma once
#include "priorityQueueMin.h"
#include "graphList/graphList.h"
#include "graphMatrix/graphMatrix.h"
#include "disjointSet.h"

namespace KRUSKAL
{
    template <typename T, typename U>
    Elem<Node<T, U>> *findInElements(Elem<Node<T, U>> **elements, Node<T, U> *node, int size);

    template <typename T, typename U>
    GraphList<T, U> kruskal(GraphList<T, U> &graph);

    template <typename T, typename U>
    Elem<NodeMatrix<T, U>> *findInElements(Elem<NodeMatrix<T, U>> **elements, NodeMatrix<T, U> *node, int size);

    template <typename T, typename U>
    GraphMatrix<T, U> kruskal(GraphMatrix<T, U> &graph);
}

#include "../src/kruskal.cpp"
