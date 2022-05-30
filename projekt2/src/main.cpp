#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <chrono>
#include <fstream>
#include <algorithm>

#include "../headers/priorityQueueMin.h"
#include "../headers/graphList/graphList.h"
#include "../headers/graphMatrix/graphMatrix.h"
#include "../headers/disjointSet.h"
#include "../headers/kruskal.h"
#include "../headers/prima.h"

struct EdgeIndexes
{
    int index_one;
    int index_two;
};

GraphList<int, int> generateGraph(int amount_of_vertexes, double density_of_edges)
{

    GraphList<int, int> result;
    int *numbs = new int[amount_of_vertexes];
    int size_of_edges_max = (amount_of_vertexes * ((amount_of_vertexes - 1))) / 2;
    EdgeIndexes *numbs_for_edges = new EdgeIndexes[size_of_edges_max];

    for (int index = 0; index < amount_of_vertexes; ++index)
    {
        numbs[index] = index;
    }

    int index_of_vertex_one = 0;
    int index_of_vertex_two = 1;
    int current_amount_left = (amount_of_vertexes - 1);
    for (int index = 0; index < size_of_edges_max; ++index)
    {
        if (index_of_vertex_one == index_of_vertex_two)
        {
            index_of_vertex_two++;
        }

        numbs_for_edges[index] = EdgeIndexes{index_of_vertex_one, index_of_vertex_two};

        current_amount_left--;
        index_of_vertex_two++;

        if (current_amount_left <= 0)
        {
            index_of_vertex_one++;
            current_amount_left = amount_of_vertexes - 1 - index_of_vertex_one;
            index_of_vertex_two = index_of_vertex_one + 1;
        }
    }

    std::random_shuffle(numbs, numbs + amount_of_vertexes);
    std::random_shuffle(numbs_for_edges, numbs_for_edges + size_of_edges_max);

    Node<int, int> **vertexes = new Node<int, int> *[amount_of_vertexes];

    for (int index = 0; index < amount_of_vertexes; ++index)
    {
        vertexes[index] = result.insertVertex(numbs[index]);
    }

    for (int index = 0; index < int((density_of_edges / 100) * size_of_edges_max); ++index)
    {
        result.insertEdge(*vertexes[numbs_for_edges[index].index_one], *vertexes[numbs_for_edges[index].index_two], rand() % 100 + 1);
    }

    delete[] vertexes;
    delete[] numbs;
    delete[] numbs_for_edges;

    return result;
}

GraphMatrix<int, int> generateGraph_matrix(int amount_of_vertexes, double density_of_edges)
{

    GraphMatrix<int, int> result;
    int *numbs = new int[amount_of_vertexes];
    int size_of_edges_max = (amount_of_vertexes * ((amount_of_vertexes - 1))) / 2;
    EdgeIndexes *numbs_for_edges = new EdgeIndexes[size_of_edges_max];

    for (int index = 0; index < amount_of_vertexes; ++index)
    {
        numbs[index] = index;
    }

    int index_of_vertex_one = 0;
    int index_of_vertex_two = 1;
    int current_amount_left = (amount_of_vertexes - 1);
    for (int index = 0; index < size_of_edges_max; ++index)
    {
        if (index_of_vertex_one == index_of_vertex_two)
        {
            index_of_vertex_two++;
        }

        numbs_for_edges[index] = EdgeIndexes{
            index_of_vertex_one,
            index_of_vertex_two};
        current_amount_left--;
        index_of_vertex_two++;

        if (current_amount_left <= 0)
        {
            index_of_vertex_one++;
            current_amount_left = amount_of_vertexes - 1 - index_of_vertex_one;
            index_of_vertex_two = index_of_vertex_one + 1;
        }
    }

    std::random_shuffle(numbs, numbs + amount_of_vertexes);
    std::random_shuffle(numbs_for_edges, numbs_for_edges + size_of_edges_max);

    NodeMatrix<int, int> **vertexes = new NodeMatrix<int, int> *[amount_of_vertexes];

    for (int index = 0; index < amount_of_vertexes; ++index)
    {
        vertexes[index] = result.insertVertex(numbs[index]);
    }

    for (int index = 0; index < int((density_of_edges / 100) * size_of_edges_max); ++index)
    {
        result.insertEdge(*vertexes[numbs_for_edges[index].index_one], *vertexes[numbs_for_edges[index].index_two], rand() % 100 + 1);
    }

    delete[] vertexes;
    delete[] numbs;
    delete[] numbs_for_edges;

    return result;
}

struct Result
{
    double result_kruskal_list;
    double result_prima_list;
    double result_kruskal_matrix;
    double result_prima_matrix;
};

Result generate_raport(int amount_of_tries, int amount_of_vertexes, double density_of_edges)
{
    double result_kruskal_list = 0;
    double result_prima_list = 0;
    double result_kruskal_matrix = 0;
    double result_prima_matrix = 0;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    for (int index = 0; index < amount_of_tries; ++index)
    {
        GraphList<int, int> graph_list = generateGraph(amount_of_vertexes, density_of_edges);
        GraphMatrix<int, int> graph_matrix = generateGraph_matrix(amount_of_vertexes, density_of_edges);

        begin = std::chrono::steady_clock::now();
        KRUSKAL::kruskal(graph_list);
        end = std::chrono::steady_clock::now();

        result_kruskal_list += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

        begin = std::chrono::steady_clock::now();
        PRIMA::prima(graph_list);
        end = std::chrono::steady_clock::now();

        result_prima_list += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

        begin = std::chrono::steady_clock::now();
        KRUSKAL::kruskal(graph_matrix);
        end = std::chrono::steady_clock::now();

        result_kruskal_matrix += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

        begin = std::chrono::steady_clock::now();
        PRIMA::prima(graph_matrix);
        end = std::chrono::steady_clock::now();

        result_prima_matrix += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    }

    Result result = Result{result_kruskal_list / amount_of_tries, result_prima_list / amount_of_tries, result_kruskal_matrix / amount_of_tries, result_prima_matrix / amount_of_tries};
    std::cout << "Dla " << amount_of_vertexes << " wiezcholkow oraz " << density_of_edges << "% gestosci:\n";
    std::cout << result.result_kruskal_list << " " << result.result_prima_list << " : " << result.result_kruskal_matrix << " " << result.result_prima_matrix << "\n";
    return result;
}

int main()
{

    srand(time(NULL));

    std::cout.precision(2);
    std::cout << std::fixed;

    std::string name_of_file = "";

    std::cout << "Podaj nazwe pliku:\n";
    std::cin >> name_of_file;

    std::ofstream file;

    file.open(name_of_file + ".txt", std::ios_base::app);
    file.precision(2);
    file << std::fixed;

    int vertexes[5] = {10, 50, 100, 500, 1000};
    int densities[4] = {25,
                        50,
                        75,
                        100};

    file << "Ile wiezcholkow,Jaka gestosc,Kruskal list,Prim list,Kruskal matrix,Prim matrix\n";
    for (int density_index = 0; density_index < sizeof(densities) / sizeof(*densities); ++density_index)
    {
        for (int vertex_index = 0; vertex_index < sizeof(vertexes) / sizeof(*vertexes); ++vertex_index)
        {
            Result result = generate_raport(100, vertexes[vertex_index], densities[density_index]);

            file << vertexes[vertex_index] << "," << densities[density_index] << "," << result.result_kruskal_list << "," << result.result_prima_list << "," << result.result_kruskal_matrix << "," << result.result_prima_matrix << "\n";
        }
    }

    file << "\n";

    file.close();

    // GraphMatrix<char, int> graph;
    // NodeMatrix<char, int> *node1 = graph.insertVertex('a');
    // NodeMatrix<char, int> *node2 = graph.insertVertex('b');
    // NodeMatrix<char, int> *node3 = graph.insertVertex('c');
    // NodeMatrix<char, int> *node4 = graph.insertVertex('d');
    // NodeMatrix<char, int> *node5 = graph.insertVertex('e');
    // NodeMatrix<char, int> *node6 = graph.insertVertex('f');

    // graph.insertEdge(*node1, *node2, 5);
    // graph.insertEdge(*node1, *node5, 5);
    // graph.insertEdge(*node2, *node3, 1);
    // graph.insertEdge(*node2, *node4, 4);
    // graph.insertEdge(*node3, *node4, 4);
    // graph.insertEdge(*node3, *node6, 3);
    // graph.insertEdge(*node6, *node4, 2);
    // graph.insertEdge(*node6, *node5, 3);

    // graph.showGraph();
    // PRIMA::prima(graph);

    return 0;
}