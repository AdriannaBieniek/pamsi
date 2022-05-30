#pragma once

template <typename T, typename U>
struct NodeMatrix
{
    T value;
    NodeMatrix<T, U> *next;
    NodeMatrix<T, U> *previous;
    int index;
};

template <typename T, typename U>
struct EdgeMatrix
{
    U value;
    NodeMatrix<T, U> *first_node;
    NodeMatrix<T, U> *second_node;

    bool operator>(const EdgeMatrix<T, U> &other) const;
    bool operator>=(const EdgeMatrix<T, U> &other) const;
    bool operator==(const EdgeMatrix<T, U> &other) const;
    bool operator<(const EdgeMatrix<T, U> &other) const;
    bool operator<=(const EdgeMatrix<T, U> &other) const;
};

template <typename T, typename U>
class GraphMatrix
{
private:
    NodeMatrix<T, U> *vertexes;
    EdgeMatrix<T, U> ***matrix_of_incidents;
    int amount_of_vertexes;
    int amount_of_edges;
    int size;

public:
    GraphMatrix();
    ~GraphMatrix();
    NodeMatrix<T, U> *insertVertex(T value);
    EdgeMatrix<T, U> *insertEdge(NodeMatrix<T, U> &vertex_one, NodeMatrix<T, U> &vertex_two, U value);
    void removeVertex(NodeMatrix<T, U> &vertex);
    void removeEdge(EdgeMatrix<T, U> &edge);
    void showGraph() const;
    NodeMatrix<T, U> *getHeadVertex();
    int getAmountOfVertexes();
    int getAmountOfEdges();
    EdgeMatrix<T, U> ***getMatrix();
    NodeMatrix<T, U> *doesContain(T value);
    EdgeMatrix<T, U> *doesContainEdge(NodeMatrix<T, U> &vertex_one, NodeMatrix<T, U> &vertex_two);
};

#include "../../src/graphMatrix/graphMatrix.cpp"
