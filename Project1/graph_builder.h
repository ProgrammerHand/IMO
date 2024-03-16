#pragma once
#include <vector>

// struktura zwracana przez buildGraph
struct Result {
    // graf (w postaci macierzy odległości)
    std::vector<std::vector<int>> graph;
    // tablica o długości równej ilości wierzchołków, która wskazuje, czy dany wierzchołek jest już w grafie (True) czy nie (False)
    std::vector<bool> isInGraph;
    // ostateczna długość cyklu (suma długości krawędzi grafu)
    int totalLength;
};

class GraphBuilder {
public:
    // zwraca Result, buduje graf na podstawie pierwotnej macierzy odległości, tablicy z informacją o dostępnych wierzchołkach i docelowej wielkości grafu
    static Result buildGraph(const std::vector<std::vector<int>>& distanceMatrix, std::vector<bool> isInGraph, int graphSize);
};
