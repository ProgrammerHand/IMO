#include "graph_builder.h"
#include "vertex_manager.h"
#include <iostream>
#include <limits>

// zwraca Result, buduje graf na podstawie pierwotnej macierzy odległości, tablicy z informacją o dostępnych wierzchołkach i docelowej wielkości grafu
Result GraphBuilder::buildGraph(const std::vector<std::vector<int>>& distanceMatrix, std::vector<bool> isInGraph, int graphSize) {
    // ilość wszystkich wierzchołków
    int verticesNum = distanceMatrix.size();
    // aktualna ilość wierzchołków w grafie
    int currGraphSize = 0;
    // aktualna długość cyklu
    int cycleLength = 0;

    // graf jako macierz odległości; macierz jest wielkości pierwotnej macierzy odległości; macierz jest wypełniona zerami (0 -> nie ma krawędzi między wierzchołkiem o indeksie wiersza a wierzchołkiem o indeksie kolumny)
    std::vector<std::vector<int>> graph(distanceMatrix.size(), std::vector<int>(distanceMatrix[0].size(), 0));

    // losowo wybierz wierzchołek początkowy
    int vertex1 = VertexManager::getRandomVertex(distanceMatrix);
    // jeżeli wybrany wierzchołek jest już w poprzednim grafie, szukaj innego do skutku
    while (isInGraph[vertex1]){
        vertex1 = VertexManager::getRandomVertex(distanceMatrix);
    }
    // zaznacz dany wierzchołek jako użyty w grafie
    isInGraph[vertex1] = true;
    // zwiększ wielkość grafu
    currGraphSize++;
    // nie aktualizujemy macierzy odległości bo nie ma jeszcze żadnej krawędzi

    // znajdź drugi wierzchołek, najbliższy do pierwszego
    int vertex2 = VertexManager::findClosestVertex(distanceMatrix, vertex1, isInGraph);

    // aktualizuj macierz odległości 
    graph[vertex1][vertex2] = distanceMatrix[vertex1][vertex2];
    graph[vertex2][vertex1] = distanceMatrix[vertex2][vertex1];
    // zaznacz drugi wierzchołek jako użyty w grafie
    isInGraph[vertex2] = true;
    // zwiększ wielkość grafu
    currGraphSize++;
    // zwiększ długość ścieżek w grafie
    cycleLength = cycleLength + distanceMatrix[vertex1][vertex2];

    // znajdź wierzchołek tworzący pierwszy cykl w grafie
    int vertex3 = VertexManager::findVertexForCycle(distanceMatrix, vertex1, vertex2, isInGraph);

    // aktualizuj macierz odległości, użyte wierzchołki, wielkość grafu, długość cyklu
    graph[vertex2][vertex3] = distanceMatrix[vertex2][vertex3];
    graph[vertex3][vertex2] = distanceMatrix[vertex3][vertex2];
    graph[vertex3][vertex1] = distanceMatrix[vertex3][vertex1];
    graph[vertex1][vertex3] = distanceMatrix[vertex1][vertex3];
    isInGraph[vertex3] = true;
    currGraphSize++;
    cycleLength = cycleLength + distanceMatrix[vertex2][vertex3] + distanceMatrix[vertex3][vertex1];

    // najdłuższa krawędź w grafie
    int maxDistance;
    // "początkowy" wierzchołek najdłuższej krawędzi w grafie (graf jest nieskierowany)
    int maxDistanceEdgeStart;
    // "końcowy" wierzchołek najdłuższej krawędzi
    int maxDistanceEdgeEnd;

    // dopóki liczba wierzchołków nie będzie równa zadanej liczbie wierzchołków
    while (currGraphSize < graphSize) {
        // ustaw dystans na mniejszy od wszystkich dystansów w grafie
        maxDistance = -1;
        
        // dla każdego wierzchołka
        for (int i = 0; i < graph.size(); i++) {
            // o ile jest w grafie
            if (isInGraph[i]) {
                // dla wszystkich możliwych połączeń tego wierzchołka
                for (int j = 0; j < graph[i].size(); j++) {
                    // rozważaj tylko te wierzchołki, które są w grafie
                    if (isInGraph[j]) {
                        // jeśli odległość między wierzchołkami jest większa niż dotychczasowa maksymalna długość
                        if (graph[i][j] > maxDistance) {
                            // zaktualizuj maksymalną odległość
                            maxDistance = graph[i][j];
                            // zapisz wierzchołki, dla których znaleziono tą odległość
                            maxDistanceEdgeStart = i;
                            maxDistanceEdgeEnd = j;
                        }
                    }
                }
            }
        }

        // odejmij długość usuwanej krawędzi od łącznej długości cyklu
        cycleLength = cycleLength - graph[maxDistanceEdgeEnd][maxDistanceEdgeStart];
        // usuń krawędź
        graph[maxDistanceEdgeStart][maxDistanceEdgeEnd] = 0;
        graph[maxDistanceEdgeEnd][maxDistanceEdgeStart] = 0;

        // poszukaj nieużytego jeszcze wierzchołka, którego dodanie spowoduje najmniejszy wzrost cyklu
        int newVertex = VertexManager::findVertexForCycle(distanceMatrix, maxDistanceEdgeStart, maxDistanceEdgeEnd, isInGraph);

        // aktualizuj macierz odległości (dodaj krawędzie), użyte wierzchołki, wielkość grafu, długość cyklu
        graph[maxDistanceEdgeStart][newVertex] = distanceMatrix[maxDistanceEdgeStart][newVertex];
        graph[newVertex][maxDistanceEdgeStart] = distanceMatrix[newVertex][maxDistanceEdgeStart];
        graph[newVertex][maxDistanceEdgeEnd] = distanceMatrix[newVertex][maxDistanceEdgeEnd];
        graph[maxDistanceEdgeEnd][newVertex] = distanceMatrix[maxDistanceEdgeEnd][newVertex];
        isInGraph[newVertex] = true;
        cycleLength = cycleLength + distanceMatrix[newVertex][maxDistanceEdgeEnd] + distanceMatrix[maxDistanceEdgeStart][newVertex];
        currGraphSize++;
    }

    // stwórz strukturę, która będzie zwrócona
    Result result;
    // graf (macierz odległości)
    result.graph = graph;
    // tablica z zaznaczonymi użytymi wierzchołkami
    result.isInGraph = isInGraph;
    // długość cyklu
    result.totalLength = cycleLength;

    return result;
}
