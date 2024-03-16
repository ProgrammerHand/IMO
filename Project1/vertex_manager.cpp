#include "vertex_manager.h"
#include <random>
#include <chrono>
#include <iostream>
#include <limits> 

// na podstawie macierzy odległości wybiera i zwraca losowy wierzchołek
int VertexManager::getRandomVertex(const std::vector<std::vector<int>>& distanceMatrix) {

    // wybierz seed na podstawie aktualnego czasu
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // deklaracja generatora liczb losowych używając seed'a
    std::mt19937 gen(seed);

    // liczba wierzchołków
    int verticesNum = distanceMatrix.size();

    // uniform distribution of ints o długości verticesNum
    std::uniform_int_distribution<int> rowDist(0, verticesNum - 1);
    // wybór losowego wierzchołka z użyciem generatora
    int chosenVertex = rowDist(gen);

    // zwróć wybrany wierzchołek
    return chosenVertex;
}

// na podstawie macierzy odlełości i istniejącego wierzchołka, zwraca najbliższy mu wierzchołek niebędący jeszcze w grafie
int VertexManager::findClosestVertex(const std::vector<std::vector<int>>& distanceMatrix, int vertex, std::vector<bool> isInGraph) {

    // liczba wszystkich wierzchołków
    int verticesNum = distanceMatrix[vertex].size();
    // indeks najbliższego wierzchołka (wybrana przeze mnie wartość początkowa to 0)
    int closestVertexIndex = 0;
    // minimalny dystans (wartość początkowa to maksymalna wartość jaką może pomieścić typ int)
    int minDistance = std::numeric_limits<int>::max();

    // dla każdego wierzchołka
    for (int i = 0; i < verticesNum; ++i) {
        // jeśli wierzchołka nie ma jeszcze w grafie i dystans jest mniejszy od najmniejszego dotychczas znalezionego
        if (!isInGraph[i] && distanceMatrix[vertex][i] < minDistance) {
            // zaktualizuj najmniejszy dystans
            minDistance = distanceMatrix[vertex][i];
            // zaktualizuj najbliższy wierzchołek
            closestVertexIndex = i;
        }
    }

    // po przeszukaniu wszystkich wierzchołków, zwróć najbliższy
    return closestVertexIndex;
}

// zwraca wierzchołek, który razem z dwoma podamymi wierzchołkami da cykl o najmniejszej możliwej długości
int VertexManager::findVertexForCycle(const std::vector<std::vector<int>>& distanceMatrix, int vertex1, int vertex2, std::vector<bool> isInGraph) {

    // liczba wierzchołków 
    int verticesNum = distanceMatrix.size();
    // indeks szukanego wierzchołka, początkowo 0
    int chosenVertex = 0;
    // minimalna długość, początkowo (wartość początkowa to maksymalna wartość jaką może pomieścić typ int)
    int minLength = std::numeric_limits<int>::max();

    // dla każdego wierzchołka
    for (int i = 0; i < verticesNum; i++) {
        // jeśli wierzchołka nie ma jeszcze w grafie
        if (i != vertex1 && i != vertex2 && !isInGraph[i]) {
            // wylicz długość cyklu z tym wierzchołkiem
            int cycleLength = distanceMatrix[vertex2][i] + distanceMatrix[i][vertex1];
            // jeśli długość cyklu jest mniejsza od poprzednio znalezionych cykli
            if (cycleLength < minLength) {
                // zaktualizuj minimalną znalezioną długość cyklu
                minLength = cycleLength;
                // aktualizuj najlepszy dotychczasowy wierzchołek
                chosenVertex = i;
            }
        }
    }

    // po sprawdzeniu wszystkich wierzchołków, zwróć najlepszy (dający cykl o minimalnej długości)
    return chosenVertex;
}

