#include "../headers/kruskal.h"

template <typename T, typename U>
Elem<Node<T, U> > *KRUSKAL::findInElements(Elem<Node<T, U> > **elements, Node<T, U> *node, int size)
{

    for (int index = 0; index < size; ++index)
    {
        if (elements[index]->value == node)
            return elements[index];
    }

    return nullptr;
}

template <typename T, typename U>
GraphList<T, U> KRUSKAL::kruskal(GraphList<T, U> &graph)
{
    GraphList<T, U> result;
    DisjointSet<Node<T, U> > disjointSet(graph.getAmountOfVertexes());
    PriorityQueueMin<Edge<T, U> > queue(graph.getAmountOfEdges());
    Elem<Node<T, U> > **elements = new Elem<Node<T, U> > *[graph.getAmountOfVertexes()];

    Node<T, U> *pointer_vertex = graph.getHeadVertex();

    int index = 0;
    while (pointer_vertex != nullptr)
    {
        elements[index] = disjointSet.makeSet(pointer_vertex);
        index++;
        pointer_vertex = pointer_vertex->next;
    }

    Edge<T, U> *pointer_edge = graph.getHeadEdges();

    while (pointer_edge != nullptr)
    {
        queue.enqueue(*pointer_edge);
        pointer_edge = pointer_edge->next;
    }

    while (!queue.isEmpty() && result.getAmountOfVertexes() < graph.getAmountOfVertexes())
    {
        // queue.print();
        Edge<T, U> smallest_edge = queue.removeMin();

        if (disjointSet.findSet(*findInElements(elements, smallest_edge.first_node, graph.getAmountOfVertexes())) != disjointSet.findSet(*findInElements(elements, smallest_edge.second_node, graph.getAmountOfVertexes())))
        {
            Node<T, U> *vertex_one = result.insertVertex(smallest_edge.first_node->value);
            Node<T, U> *vertex_two = result.insertVertex(smallest_edge.second_node->value);
            result.insertEdge(*vertex_one, *vertex_two, smallest_edge.value);
            disjointSet.unionSets(*findInElements(elements, smallest_edge.first_node, graph.getAmountOfVertexes()), *findInElements(elements, smallest_edge.second_node, graph.getAmountOfVertexes()));
        }
    }
    delete[] elements;
    // result.showGraph();
    return result;
}

template <typename T, typename U>
Elem<NodeMatrix<T, U> > *KRUSKAL::findInElements(Elem<NodeMatrix<T, U> > **elements, NodeMatrix<T, U> *node, int size)
{

    for (int index = 0; index < size; ++index)
    {
        if (elements[index]->value == node)
            return elements[index];
    }

    return nullptr;
}

template <typename T, typename U>
GraphMatrix<T, U> KRUSKAL::kruskal(GraphMatrix<T, U> &graph)
{
    GraphMatrix<T, U> result;
    DisjointSet<NodeMatrix<T, U> > disjointSet(graph.getAmountOfVertexes());
    PriorityQueueMin<EdgeMatrix<T, U> > queue(graph.getAmountOfEdges());
    Elem<NodeMatrix<T, U> > **elements = new Elem<NodeMatrix<T, U> > *[graph.getAmountOfVertexes()];

    NodeMatrix<T, U> *pointer_vertex = graph.getHeadVertex();

    int index = 0;
    while (pointer_vertex != nullptr)
    {
        elements[index] = disjointSet.makeSet(pointer_vertex);
        index++;
        pointer_vertex = pointer_vertex->next;
    }

    EdgeMatrix<T, U> ***pointer_edge = graph.getMatrix();

    for (int index_row = 0; index_row < graph.getAmountOfVertexes(); ++index_row)
    {
        for (int index_column = index_row; index_column < graph.getAmountOfVertexes(); ++index_column)
        {
            if (pointer_edge[index_row][index_column] != nullptr)
                queue.enqueue(*pointer_edge[index_row][index_column]);
        }
    }

    while (!queue.isEmpty() && result.getAmountOfVertexes() < graph.getAmountOfVertexes())
    {
        EdgeMatrix<T, U> smallest_edge = queue.removeMin();

        if (disjointSet.findSet(*findInElements(elements, smallest_edge.first_node, graph.getAmountOfVertexes())) != disjointSet.findSet(*findInElements(elements, smallest_edge.second_node, graph.getAmountOfVertexes())))
        {

            NodeMatrix<T, U> *vertex_one = result.insertVertex(smallest_edge.first_node->value);
            NodeMatrix<T, U> *vertex_two = result.insertVertex(smallest_edge.second_node->value);
            result.insertEdge(*vertex_one, *vertex_two, smallest_edge.value);
            disjointSet.unionSets(*findInElements(elements, smallest_edge.first_node, graph.getAmountOfVertexes()), *findInElements(elements, smallest_edge.second_node, graph.getAmountOfVertexes()));
        }
    }

    delete[] elements;
    // result.showGraph();
    return result;
}
