#pragma once
#include "priorityQueueMin.h"
#include "graphList/graphList.h"
#include "graphMatrix/graphMatrix.h"
#include "disjointSet.h"

namespace PRIMA
{
    template <typename T, typename U>
    struct Distance_vertex
    {
        Node<T, U> *vertex;
        U distance;
    };

    template <typename T, typename U>
    struct Distance_vertex_matrix
    {
        NodeMatrix<T, U> *vertex;
        U distance;
    };
    template <typename T, typename U>
    Distance_vertex<T, U> *findInDistances(Distance_vertex<T, U> **distances, Node<T, U> *node, int size);

    template <typename T, typename U>
    Elem<Node<T, U>> *findInElements(Elem<Node<T, U>> **elements, Node<T, U> *node, int size);

    template <typename T, typename U>
    Distance_vertex_matrix<T, U> *findInDistances(Distance_vertex_matrix<T, U> **distances, NodeMatrix<T, U> *node, int size);

    template <typename T, typename U>
    Elem<NodeMatrix<T, U>> *findInElements(Elem<NodeMatrix<T, U>> **elements, NodeMatrix<T, U> *node, int size);

    template <typename T, typename U>
    GraphList<T, U> prima(GraphList<T, U> &graph);

    template <typename T, typename U>
    GraphMatrix<T, U> prima(GraphMatrix<T, U> &graph);

}

#include "../src/prima.cpp"
