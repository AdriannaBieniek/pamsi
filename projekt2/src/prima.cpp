#include "../headers/prima.h"

template <typename T, typename U>
PRIMA::Distance_vertex<T, U> *PRIMA::findInDistances(Distance_vertex<T, U> **distances, Node<T, U> *node, int size)
{
    for (int index = 0; index < size; ++index)
    {
        if (distances[index]->vertex == node)
            return distances[index];
    }

    return nullptr;
}

template <typename T, typename U>
Elem<Node<T, U>> *PRIMA::findInElements(Elem<Node<T, U>> **elements, Node<T, U> *node, int size)
{

    for (int index = 0; index < size; ++index)
    {
        if (elements[index]->value == node)
            return elements[index];
    }

    return nullptr;
}

template <typename T, typename U>
PRIMA::Distance_vertex_matrix<T, U> *PRIMA::findInDistances(Distance_vertex_matrix<T, U> **distances, NodeMatrix<T, U> *node, int size)
{
    for (int index = 0; index < size; ++index)
    {
        if (distances[index]->vertex == node)
            return distances[index];
    }

    return nullptr;
}

template <typename T, typename U>
Elem<NodeMatrix<T, U>> *PRIMA::findInElements(Elem<NodeMatrix<T, U>> **elements, NodeMatrix<T, U> *node, int size)
{

    for (int index = 0; index < size; ++index)
    {
        if (elements[index]->value == node)
            return elements[index];
    }

    return nullptr;
}

template <typename T, typename U>
GraphList<T, U> PRIMA::prima(GraphList<T, U> &graph)
{
    GraphList<T, U> result;
    PriorityQueueMin<Edge<T, U>> queue(graph.getAmountOfEdges());
    Distance_vertex<T, U> **distances = new Distance_vertex<T, U> *[graph.getAmountOfVertexes()];
    Elem<Node<T, U>> **elements = new Elem<Node<T, U>> *[graph.getAmountOfVertexes()];
    DisjointSet<Node<T, U>> disjointSet(graph.getAmountOfVertexes());
    Node<T, U> **previous_vertexes = new Node<T, U> *[graph.getAmountOfVertexes()];

    Node<T, U> *current_node = graph.getHeadVertex();

    distances[0] = new Distance_vertex<T, U>{current_node, 0};
    elements[0] = disjointSet.makeSet(current_node);
    Node<T, U> *other_nodes = current_node->next;

    int index = 1;
    while (other_nodes != nullptr)
    {
        distances[index] = new Distance_vertex<T, U>{other_nodes, std::numeric_limits<U>::max()};
        elements[index] = disjointSet.makeSet(other_nodes);
        other_nodes = other_nodes->next;
        index++;
    }

    Incident<T, U> *incidents_of_start_node = current_node->incident;
    while (incidents_of_start_node != nullptr)
    {
        queue.enqueue(*incidents_of_start_node->edge);
        incidents_of_start_node = incidents_of_start_node->next;
    }
    previous_vertexes[0] = current_node;
    index = 1;
    while (!queue.isEmpty() && result.getAmountOfVertexes() < graph.getAmountOfVertexes())
    {
        Edge<T, U> min_edge = queue.removeMin();
        current_node = current_node != min_edge.first_node ? min_edge.first_node : min_edge.second_node;
        int index_vertex = 0;
        for (; index_vertex < index; ++index_vertex)
        {
            if (current_node == previous_vertexes[index_vertex])
            {
                current_node = current_node == min_edge.first_node ? min_edge.first_node : min_edge.second_node;
                break;
            }
        }

        if (index_vertex == index)
        {
            previous_vertexes[index] = current_node;
            if (index < graph.getAmountOfVertexes())
                index++;
        }

        if (disjointSet.findSet(*findInElements(elements, min_edge.first_node, graph.getAmountOfVertexes())) != disjointSet.findSet(*findInElements(elements, min_edge.second_node, graph.getAmountOfVertexes())))
        {
            Node<T, U> *vertex_one = result.insertVertex(min_edge.first_node->value);
            Node<T, U> *vertex_two = result.insertVertex(min_edge.second_node->value);
            result.insertEdge(*vertex_one, *vertex_two, min_edge.value);
            disjointSet.unionSets(*findInElements(elements, min_edge.first_node, graph.getAmountOfVertexes()), *findInElements(elements, min_edge.second_node, graph.getAmountOfVertexes()));

            Incident<T, U> *incidents_next_node = current_node->incident;

            while (incidents_next_node != nullptr)
            {

                Node<T, U> *next_node = current_node != incidents_next_node->edge->first_node ? incidents_next_node->edge->first_node : incidents_next_node->edge->second_node;
                Distance_vertex<T, U> *next_node_distance = findInDistances(distances, next_node, graph.getAmountOfVertexes());
                if (incidents_next_node->edge->value < next_node_distance->distance)
                {

                    if (result.doesContainEdge(*incidents_next_node->edge->first_node, *incidents_next_node->edge->second_node) == nullptr)
                    {
                        next_node_distance->distance = incidents_next_node->edge->value;
                        queue.enqueue(*incidents_next_node->edge);
                    }
                }

                incidents_next_node = incidents_next_node->next;
            }
        }
    }

    // result.showGraph();
    delete[] distances;
    return result;
}

template <typename T, typename U>
GraphMatrix<T, U> PRIMA::prima(GraphMatrix<T, U> &graph)
{
    GraphMatrix<T, U> result;
    PriorityQueueMin<EdgeMatrix<T, U>> queue(graph.getAmountOfEdges());
    Distance_vertex_matrix<T, U> **distances = new Distance_vertex_matrix<T, U> *[graph.getAmountOfVertexes()];
    Elem<NodeMatrix<T, U>> **elements = new Elem<NodeMatrix<T, U>> *[graph.getAmountOfVertexes()];
    DisjointSet<NodeMatrix<T, U>> disjointSet(graph.getAmountOfVertexes());
    NodeMatrix<T, U> **previous_vertexes = new NodeMatrix<T, U> *[graph.getAmountOfVertexes()];

    NodeMatrix<T, U> *current_node = graph.getHeadVertex();

    distances[0] = new Distance_vertex_matrix<T, U>{current_node, 0};
    elements[0] = disjointSet.makeSet(current_node);
    NodeMatrix<T, U> *other_nodes = current_node->next;

    int index = 1;
    while (other_nodes != nullptr)
    {
        distances[index] = new Distance_vertex_matrix<T, U>{other_nodes, std::numeric_limits<U>::max()};
        elements[index] = disjointSet.makeSet(other_nodes);
        other_nodes = other_nodes->next;
        index++;
    }

    for (int index_vertex = 0; index_vertex < graph.getAmountOfVertexes(); ++index_vertex)
    {
        if (graph.getMatrix()[current_node->index][index_vertex] != nullptr)
            queue.enqueue(*graph.getMatrix()[current_node->index][index_vertex]);
    }

    previous_vertexes[0] = current_node;
    index = 1;

    while (!queue.isEmpty() && result.getAmountOfVertexes() < graph.getAmountOfVertexes())
    {
        EdgeMatrix<T, U> min_edge = queue.removeMin();
        current_node = current_node != min_edge.first_node ? min_edge.first_node : min_edge.second_node;
        int index_vertex = 0;
        for (; index_vertex < index; ++index_vertex)
        {
            if (current_node == previous_vertexes[index_vertex])
            {
                current_node = current_node == min_edge.first_node ? min_edge.first_node : min_edge.second_node;
                break;
            }
        }

        if (index_vertex == index)
        {
            previous_vertexes[index] = current_node;
            if (index < graph.getAmountOfVertexes())
                index++;
        }

        if (disjointSet.findSet(*findInElements(elements, min_edge.first_node, graph.getAmountOfVertexes())) != disjointSet.findSet(*findInElements(elements, min_edge.second_node, graph.getAmountOfVertexes())))
        {
            NodeMatrix<T, U> *vertex_one = result.insertVertex(min_edge.first_node->value);
            NodeMatrix<T, U> *vertex_two = result.insertVertex(min_edge.second_node->value);
            result.insertEdge(*vertex_one, *vertex_two, min_edge.value);
            disjointSet.unionSets(*findInElements(elements, min_edge.first_node, graph.getAmountOfVertexes()), *findInElements(elements, min_edge.second_node, graph.getAmountOfVertexes()));

            for (int index_vertex = 0; index_vertex < graph.getAmountOfVertexes(); ++index_vertex)
            {
                EdgeMatrix<T, U> *temp_edge = graph.getMatrix()[current_node->index][index_vertex];
                if (temp_edge != nullptr)
                {

                    NodeMatrix<T, U> *next_node = current_node != temp_edge->first_node ? temp_edge->first_node : temp_edge->second_node;
                    Distance_vertex_matrix<T, U> *next_node_distance = findInDistances(distances, next_node, graph.getAmountOfVertexes());

                    if (temp_edge->value < next_node_distance->distance)
                    {

                        if (result.doesContainEdge(*temp_edge->first_node, *temp_edge->second_node) == nullptr)
                        {
                            next_node_distance->distance = temp_edge->value;
                            queue.enqueue(*temp_edge);
                        }
                    }
                }
            }
        }
    }

    // result.showGraph();
    delete[] previous_vertexes;
    delete[] distances;
    return result;
}
