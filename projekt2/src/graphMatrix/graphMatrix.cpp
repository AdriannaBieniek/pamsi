#include "../../headers/graphMatrix/graphMatrix.h"

template <typename T, typename U>
bool EdgeMatrix<T, U>::operator>(const EdgeMatrix<T, U> &other) const
{
    return value > other.value;
}

template <typename T, typename U>
bool EdgeMatrix<T, U>::operator>=(const EdgeMatrix<T, U> &other) const
{
    return value >= other.value;
}

template <typename T, typename U>
bool EdgeMatrix<T, U>::operator==(const EdgeMatrix<T, U> &other) const
{
    return value == other.value && ((first_node == other.first_node && second_node == other.second_node) || (second_node == other.first_node && first_node == other.second_node));
}

template <typename T, typename U>
bool EdgeMatrix<T, U>::operator<(const EdgeMatrix<T, U> &other) const
{
    return value < other.value;
}

template <typename T, typename U>
bool EdgeMatrix<T, U>::operator<=(const EdgeMatrix<T, U> &other) const
{
    return value <= other.value;
}

// template <typename T, typename U>
// std::ostream &operator<<(std::ostream &os, const EdgeMatrix<T, U> &edge)
// {
//     if (edge.first_node != nullptr && edge.second_node != nullptr)
//         os << edge.value << ":" << edge.first_node->value << "::" << edge.second_node->value;
//     else
//         os << edge.value;
//     return os;
// }

// template <typename T, typename U>
// std::ostream &operator<<(std::ostream &os, const NodeMatrix<T, U> &node)
// {
//     os << node.value;
//     return os;
// }

template <typename T, typename U>
GraphMatrix<T, U>::GraphMatrix()
{
    this->vertexes = nullptr;
    this->matrix_of_incidents = new EdgeMatrix<T, U> **[0];
    this->amount_of_vertexes = 0;
    this->amount_of_edges = 0;
    this->size = 0;
}

template <typename T, typename U>
GraphMatrix<T, U>::~GraphMatrix()
{
    for (int index_row = 0; index_row < this->size; ++index_row)
    {
        delete[] this->matrix_of_incidents[index_row];
    }

    delete[] this->matrix_of_incidents;
    this->amount_of_vertexes = 0;
    this->amount_of_edges = 0;
}

template <typename T, typename U>
NodeMatrix<T, U> *GraphMatrix<T, U>::doesContain(T value)
{
    NodeMatrix<T, U> *temp_pointer_node = this->vertexes;
    while (temp_pointer_node != nullptr)
    {
        if (temp_pointer_node->value == value)
            return temp_pointer_node;
        temp_pointer_node = temp_pointer_node->next;
    }
    return nullptr;
}

template <typename T, typename U>
NodeMatrix<T, U> *GraphMatrix<T, U>::insertVertex(T value)
{
    // NodeMatrix<T, U> *doesContain = this->doesContain(value);
    // if (doesContain != nullptr)
    //     return doesContain;
    NodeMatrix<T, U> *new_node = new NodeMatrix<T, U>{
        value,
        this->vertexes, // next
        nullptr,        // prevoious
        this->size,     // index
    };

    this->size++;
    EdgeMatrix<T, U> ***temp_matrix = new EdgeMatrix<T, U> **[this->size];

    for (int index = 0; index < this->size; ++index)
    {
        temp_matrix[index] = new EdgeMatrix<T, U> *[this->size];
    }

    for (int index_row = 0; index_row < this->size; ++index_row)
    {
        for (int index_column = 0; index_column < this->size; ++index_column)
        {
            if (index_row < this->size - 1 && index_column < this->size - 1)
                temp_matrix[index_row][index_column] = this->matrix_of_incidents[index_row][index_column];
            else
                temp_matrix[index_row][index_column] = nullptr;
        }
    }

    for (int index_row = 0; index_row < this->size - 1; ++index_row)
    {
        delete[] this->matrix_of_incidents[index_row];
    }

    delete[] this->matrix_of_incidents;
    this->matrix_of_incidents = temp_matrix;

    if (this->vertexes != nullptr) // Dodanie kolejnego wierzcholka (nie pierwszego)
        this->vertexes->previous = new_node;

    this->vertexes = new_node;
    this->amount_of_vertexes++;
    return new_node;
}

template <typename T, typename U>
EdgeMatrix<T, U> *GraphMatrix<T, U>::doesContainEdge(NodeMatrix<T, U> &vertex_one, NodeMatrix<T, U> &vertex_two)
{
    for (int index_vertex = 0; index_vertex < this->amount_of_vertexes; ++index_vertex)
    {
        for (int index_edge = 0; index_edge < this->amount_of_vertexes; ++index_edge)
        {
            if (this->matrix_of_incidents[index_vertex][index_edge] != nullptr && ((this->matrix_of_incidents[index_vertex][index_edge]->first_node == &vertex_one && this->matrix_of_incidents[index_vertex][index_edge]->second_node == &vertex_two) || (this->matrix_of_incidents[index_vertex][index_edge]->first_node == &vertex_two && this->matrix_of_incidents[index_vertex][index_edge]->second_node == &vertex_one)))
                return this->matrix_of_incidents[index_vertex][index_edge];
        }
    }
    return nullptr;
}

template <typename T, typename U>
EdgeMatrix<T, U> *GraphMatrix<T, U>::insertEdge(NodeMatrix<T, U> &vertex_one, NodeMatrix<T, U> &vertex_two, U value)
{
    // EdgeMatrix<T, U> *doesContain = doesContainEdge(vertex_one, vertex_two);
    // if (doesContain != nullptr)
    //     return doesContain;

    EdgeMatrix<T, U> *
        new_edge = new EdgeMatrix<T, U>{value, &vertex_one, &vertex_two};
    this->matrix_of_incidents[vertex_one.index][vertex_two.index] = new_edge;
    this->matrix_of_incidents[vertex_two.index][vertex_one.index] = new_edge;

    this->amount_of_edges++;
    return new_edge;
}

template <typename T, typename U>
void GraphMatrix<T, U>::removeVertex(NodeMatrix<T, U> &vertex)
{
    NodeMatrix<T, U> *temp_pointer = this->vertexes;

    while (temp_pointer != nullptr)
    {
        if (temp_pointer != &vertex && temp_pointer->index > vertex.index)
            temp_pointer->index = temp_pointer->index - 1;
        temp_pointer = temp_pointer->next;
    }

    for (int index = 0; index < this->size; ++index)
    {
        this->matrix_of_incidents[vertex.index][index] = nullptr;
        this->matrix_of_incidents[index][vertex.index] = nullptr;
    }

    this->size--;
    EdgeMatrix<T, U> ***temp_matrix = new EdgeMatrix<T, U> **[this->size];

    for (int index = 0; index < this->size; ++index)
    {
        temp_matrix[index] = new EdgeMatrix<T, U> *[this->size];
    }

    for (int index_row = 0; index_row < this->size; ++index_row)
    {
        for (int index_column = 0; index_column < this->size; ++index_column)
        {
            if (index_row < vertex.index && index_column < vertex.index)
                temp_matrix[index_row][index_column] = this->matrix_of_incidents[index_row][index_column];
            else if (index_column >= vertex.index)
                temp_matrix[index_row][index_column] = this->matrix_of_incidents[index_row][index_column + 1];
            else if (index_row >= vertex.index)
                temp_matrix[index_row][index_column] = this->matrix_of_incidents[index_row + 1][index_column];
            else
                temp_matrix[index_row][index_column] = this->matrix_of_incidents[index_row + 1][index_column + 1];
        }
    }

    for (int index_row = 0; index_row < this->size - 1; ++index_row)
    {
        delete[] this->matrix_of_incidents[index_row];
    }

    delete[] this->matrix_of_incidents;
    this->matrix_of_incidents = temp_matrix;

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
void GraphMatrix<T, U>::removeEdge(EdgeMatrix<T, U> &edge)
{

    this->matrix_of_incidents[edge->first_node->index][edge->second_node->index] = nullptr;
    this->matrix_of_incidents[edge->second_node->index][edge->first_node->index] = nullptr;

    edge.first_node = nullptr;
    edge.second_node = nullptr;

    this->amount_of_edges--;
    delete &edge;
}

template <typename T, typename U>
void GraphMatrix<T, U>::showGraph() const
{
    NodeMatrix<T, U> *temp_pointer = this->vertexes;

    while (temp_pointer != nullptr)
    {
        std::cout << temp_pointer->value << " " << temp_pointer->index;

        temp_pointer = temp_pointer->next;
        std::cout << "\n";
    }

    for (int index_row = -1; index_row < this->size; ++index_row)
    {
        std::cout << index_row << "\t";
        for (int index_column = -1; index_column < this->size; ++index_column)
        {
            if (index_row == -1 && index_column != -1)
                std::cout << index_column << "\t";
            if (index_row > -1 && index_column > -1)
            {
                if (matrix_of_incidents[index_row][index_column] != nullptr)
                    std::cout << this->matrix_of_incidents[index_row][index_column]->value << "\t";
                else
                    std::cout << "n\t";
            }
        }
        std::cout << "\n";
    }
}

template <typename T, typename U>
NodeMatrix<T, U> *GraphMatrix<T, U>::getHeadVertex()
{
    return this->vertexes;
}

template <typename T, typename U>
int GraphMatrix<T, U>::getAmountOfVertexes()
{
    return this->amount_of_vertexes;
}

template <typename T, typename U>
int GraphMatrix<T, U>::getAmountOfEdges()
{
    return this->amount_of_edges;
}

template <typename T, typename U>
EdgeMatrix<T, U> ***GraphMatrix<T, U>::getMatrix()
{
    return this->matrix_of_incidents;
}
