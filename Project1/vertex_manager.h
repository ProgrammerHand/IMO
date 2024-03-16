#pragma once
#include <vector>

// klasa obsługująca wierzchołki
class VertexManager {
public:
    // zwraca losowy wierzchołek
    static int getRandomVertex(const std::vector<std::vector<int>>& distanceMatrix);
    // zwraca wierzchołek najbliższy do podanego wierzchołka
    static int findClosestVertex(const std::vector<std::vector<int>>& distanceMatrix, int vertex, std::vector<bool> isInGraph);
    // zwraca wierzchołek, który razem z dwoma podanymi wierzchołkami da najmniejszą łączną długość cyklu 
    static int findVertexForCycle(const std::vector<std::vector<int>>& distanceMatrix, int vertex1, int vertex2, std::vector<bool> isInGraph);
};



