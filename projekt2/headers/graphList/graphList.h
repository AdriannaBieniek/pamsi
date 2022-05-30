#pragma once

template <typename T, typename U>
struct Incident;

template <typename T, typename U>
struct Node
{
    T value;
    Node<T, U> *next;
    Node<T, U> *previous;
    Incident<T, U> *incident;
};

template <typename T, typename U>
struct Edge
{
    U value;
    Edge<T, U> *next;
    Edge<T, U> *previous;
    Node<T, U> *first_node;
    Node<T, U> *second_node;
    Incident<T, U> *incident_first_node;
    Incident<T, U> *incident_second_node;

    bool operator>(const Edge<T, U> &other) const;
    bool operator>=(const Edge<T, U> &other) const;
    bool operator==(const Edge<T, U> &other) const;
    bool operator<(const Edge<T, U> &other) const;
    bool operator<=(const Edge<T, U> &other) const;
};

template <typename T, typename U>
struct Incident
{
    Incident<T, U> *next;
    Incident<T, U> *previous;
    Edge<T, U> *edge;
};

template <typename T, typename U>
class GraphList
{
private:
    Node<T, U> *vertexes;
    Edge<T, U> *edges;
    int amount_of_vertexes;
    int amount_of_edges;

public:
    GraphList();
    ~GraphList();
    Node<T, U> *insertVertex(T value);
    Edge<T, U> *insertEdge(Node<T, U> &vertex_one, Node<T, U> &vertex_two, U value);
    void removeVertex(Node<T, U> &vertex);
    void removeEdge(Edge<T, U> &edge);
    void showGraph() const;
    Node<T, U> *getHeadVertex();
    Edge<T, U> *getHeadEdges();
    int getAmountOfVertexes();
    int getAmountOfEdges();
    Node<T, U> *doesContain(T value);
    Edge<T, U> *doesContainEdge(Node<T, U> &vertex_one, Node<T, U> &vertex_two);
};

#include "../../src/graphList/graphList.cpp"