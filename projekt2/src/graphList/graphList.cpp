#include "../../headers/graphList/graphList.h"

template <typename T, typename U>
bool Edge<T, U>::operator>(const Edge<T, U> &other) const
{
    return value > other.value;
}

template <typename T, typename U>
bool Edge<T, U>::operator>=(const Edge<T, U> &other) const
{
    return value >= other.value;
}

template <typename T, typename U>
bool Edge<T, U>::operator==(const Edge<T, U> &other) const
{
    return value == other.value && ((first_node == other.first_node && second_node == other.second_node) || (second_node == other.first_node && first_node == other.second_node));
}

template <typename T, typename U>
bool Edge<T, U>::operator<(const Edge<T, U> &other) const
{
    return value < other.value;
}

template <typename T, typename U>
bool Edge<T, U>::operator<=(const Edge<T, U> &other) const
{
    return value <= other.value;
}

// template <typename T, typename U>
// std::ostream &operator<<(std::ostream &os, const Edge<T, U> &edge)
// {
//     if (edge.first_node != nullptr && edge.second_node != nullptr)
//         os << edge.value << ":" << edge.first_node->value << "::" << edge.second_node->value;
//     else
//         os << edge.value;
//     return os;
// }

// template <typename T, typename U>
// std::ostream &operator<<(std::ostream &os, const Node<T, U> &node)
// {
//     os << node.value;
//     return os;
// }

template <typename T, typename U>
GraphList<T, U>::GraphList()
{
    this->vertexes = nullptr;
    this->edges = nullptr;
    this->amount_of_vertexes = 0;
    this->amount_of_edges = 0;
}

template <typename T, typename U>
GraphList<T, U>::~GraphList()
{
    if (this->vertexes != nullptr)
    {
        Node<T, U> *temp_pointer_node = this->vertexes->next;

        while (temp_pointer_node != nullptr)
        {
            delete this->vertexes;
            this->vertexes = temp_pointer_node;
            temp_pointer_node = temp_pointer_node->next;
        }
        delete this->vertexes;
        this->vertexes = nullptr;
    }

    if (this->edges != nullptr)
    {
        Edge<T, U> *temp_pointer_edge = this->edges->next;
        while (temp_pointer_edge != nullptr)
        {
            delete this->edges;
            this->edges = temp_pointer_edge;
            temp_pointer_edge = temp_pointer_edge->next;
        }
        delete this->edges;
        this->edges = nullptr;
    }
    this->amount_of_vertexes = 0;
    this->amount_of_edges = 0;
}

template <typename T, typename U>
Node<T, U> *GraphList<T, U>::doesContain(T value)
{
    Node<T, U> *temp_pointer_node = this->vertexes;
    while (temp_pointer_node != nullptr)
    {
        if (temp_pointer_node->value == value)
            return temp_pointer_node;
        temp_pointer_node = temp_pointer_node->next;
    }
    return nullptr;
}

template <typename T, typename U>
Node<T, U> *GraphList<T, U>::insertVertex(T value)
{
    // Node<T, U> *doesContains = this->doesContain(value);
    // if (doesContains != nullptr)
    //     return doesContains;
    Node<T, U> *new_node = new Node<T, U>{value, this->vertexes, nullptr, nullptr}; // wartosc, next, previous, incidents

    if (this->vertexes != nullptr)
        this->vertexes->previous = new_node;

    this->vertexes = new_node;
    this->amount_of_vertexes++;

    return new_node;
}

template <typename T, typename U>
Edge<T, U> *GraphList<T, U>::doesContainEdge(Node<T, U> &vertex_one, Node<T, U> &vertex_two)
{
    Edge<T, U> *temp_pointer_edge = this->edges;
    while (temp_pointer_edge != nullptr)
    {
        if ((temp_pointer_edge->first_node == &vertex_one && temp_pointer_edge->second_node == &vertex_two) || (temp_pointer_edge->second_node == &vertex_one && temp_pointer_edge->first_node == &vertex_two))
            return temp_pointer_edge;
        temp_pointer_edge = temp_pointer_edge->next;
    }
    return nullptr;
}

template <typename T, typename U>
Edge<T, U> *GraphList<T, U>::insertEdge(Node<T, U> &vertex_one, Node<T, U> &vertex_two, U value)
{
    // Edge<T, U> *doesContains = this->doesContainEdge(vertex_one, vertex_two);
    // if (doesContains != nullptr)
    //     return doesContains;
    Edge<T, U> *new_edge = new Edge<T, U>{value, this->edges, nullptr, &vertex_one, &vertex_two, nullptr, nullptr}; // wartosc, next, previous, pierwszy wezel, drugi weze, incident1, incident2

    Incident<T, U> *incident_first_node = new Incident<T, U>{vertex_one.incident, nullptr, new_edge}; // next, previous, edge
    Incident<T, U> *incident_second_node = new Incident<T, U>{vertex_two.incident, nullptr, new_edge};

    if (vertex_one.incident != nullptr)
        vertex_one.incident->previous = incident_first_node;
    vertex_one.incident = incident_first_node;

    if (vertex_two.incident != nullptr)
        vertex_two.incident->previous = incident_second_node;
    vertex_two.incident = incident_second_node;

    new_edge->incident_first_node = vertex_one.incident;
    new_edge->incident_second_node = vertex_two.incident;

    if (this->edges != nullptr)
        this->edges->previous = new_edge;
    this->edges = new_edge;

    this->amount_of_edges++;
    return new_edge;
}

template <typename T, typename U>
void GraphList<T, U>::removeVertex(Node<T, U> &vertex)
{
    if (vertex.incident != nullptr)
    {
        Incident<T, U> *temp_pointer = vertex.incident->next;

        while (temp_pointer != nullptr)
        {
            this->removeEdge(*vertex.incident->edge);
            vertex.incident = temp_pointer;
            temp_pointer = temp_pointer->next;
        }
        this->removeEdge(*vertex.incident->edge);
    }

    if (vertex.previous != nullptr)
        vertex.previous->next = vertex.next;

    if (vertex.next != nullptr)
        vertex.next->previous = vertex.previous;

    if (this->vertexes == &vertex && vertex.next == nullptr)
        this->vertexes = nullptr;

    if (this->vertexes == &vertex && vertex.next != nullptr)
        this->vertexes = vertex.next;

    vertex.next = nullptr;
    vertex.previous = nullptr;

    this->amount_of_vertexes--;
    delete &vertex;
}

template <typename T, typename U>
void GraphList<T, U>::removeEdge(Edge<T, U> &edge)
{
    if (edge.previous != nullptr)
        edge.previous->next = edge.next;

    if (edge.next != nullptr)
        edge.next->previous = edge.previous;

    if (this->edges == &edge && edge.next == nullptr)
        this->edges = nullptr;

    if (this->edges == &edge && edge.next != nullptr)
        this->edges = edge.next;

    edge.next = nullptr;
    edge.previous = nullptr;

    if (edge.incident_first_node->previous != nullptr)
        edge.incident_first_node->previous->next = edge.incident_first_node->next;

    if (edge.incident_first_node->next != nullptr)
        edge.incident_first_node->next->previous = edge.incident_first_node->previous;

    if (edge.first_node->incident == edge.incident_first_node && edge.incident_first_node->next == nullptr)
        edge.first_node->incident = nullptr;

    if (edge.first_node->incident == edge.incident_first_node && edge.incident_first_node->next != nullptr)
        edge.first_node->incident = edge.incident_first_node->next;

    delete edge.incident_first_node;
    edge.incident_first_node->next = nullptr;
    edge.incident_first_node->previous = nullptr;
    edge.incident_first_node = nullptr;

    if (edge.incident_second_node->previous != nullptr)
        edge.incident_second_node->previous->next = edge.incident_second_node->next;

    if (edge.incident_second_node->next != nullptr)
        edge.incident_second_node->next->previous = edge.incident_second_node->previous;

    if (edge.second_node->incident == edge.incident_second_node && edge.incident_second_node->next == nullptr)
        edge.second_node->incident = nullptr;

    if (edge.second_node->incident == edge.incident_second_node && edge.incident_second_node->next != nullptr)
        edge.second_node->incident = edge.incident_second_node->next;

    delete edge.incident_second_node;
    edge.incident_second_node->next = nullptr;
    edge.incident_second_node->previous = nullptr;
    edge.incident_second_node = nullptr;

    edge.first_node = nullptr;
    edge.second_node = nullptr;

    this->amount_of_edges--;
    delete &edge;
}

template <typename T, typename U>
void GraphList<T, U>::showGraph() const
{
    Node<T, U> *temp_pointer = this->vertexes;

    while (temp_pointer != nullptr)
    {
        std::cout << temp_pointer->value << " ";
        Incident<T, U> *incidents = temp_pointer->incident;

        while (incidents != nullptr)
        {
            std::cout << incidents->edge->value << " ";
            incidents = incidents->next;
        }

        temp_pointer = temp_pointer->next;
        std::cout << "\n";
    }
}

template <typename T, typename U>
Node<T, U> *GraphList<T, U>::getHeadVertex()
{
    return this->vertexes;
}

template <typename T, typename U>
Edge<T, U> *GraphList<T, U>::getHeadEdges()
{
    return this->edges;
}

template <typename T, typename U>
int GraphList<T, U>::getAmountOfVertexes()
{
    return this->amount_of_vertexes;
}

template <typename T, typename U>
int GraphList<T, U>::getAmountOfEdges()
{
    return this->amount_of_edges;
}
