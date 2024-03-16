#include <iostream>
#include <vector>
#include "file_management.h"
#include "distance_calculation.h"
#include "vertex_manager.h"
#include "graph_builder.h"

int main() {
    const char* file_path = "kroA100.tsp";
    
    // Read node coordinates and calculate distances
    std::vector<Point> nodes = readNodeCoordinates(file_path);

    // Create a matrix of distances
    std::vector<std::vector<int>> distanceMatrix = calculateDistanceMatrix(nodes);

    // Print the distance matrix
    // printDistanceMatrix(distanceMatrix);

    // Save the distance matrix to a file
    // saveDistanceMatrixToFile(distanceMatrix, "output.txt");

    //Example distance matrix
    /*std::vector<std::vector<int>> distanceMatrix = {
        {0, 3, 5, 6, 9, 1},
        {3, 0, 2, 7, 1, 2},
        {5, 2, 0, 4, 8, 3},
        {6, 7, 4, 0, 10, 4},
        {9, 1, 8, 10, 0, 5}, 
        {1, 2, 3, 4, 5, 0}
    };*/

    // weź liczbę wierzchołków
    int numRows = distanceMatrix.size();
    // ustal liczbę wierzchołków dla pierwszego grafu
    int numGraphRows = numRows / 2 + (numRows % 2);
    
    // stwórz tablicę o rozmiarze równym liczbie wierzchołków, ustal wartości początkowe na False (żaden wierzchołek nie jest jeszcze w grafie)
    std::vector<bool> isInGraph(numRows, false);

    // stwórz pierwszy graf
    Result result = GraphBuilder::buildGraph(distanceMatrix, isInGraph, numGraphRows);

    // pobierz wynikowy graf
    std::vector<std::vector<int>> graph = result.graph;
    // pobierz tablicę użytych wierzchołków
    isInGraph = result.isInGraph;
    // pobierz całkowitą długość cyklu

    // wyświetl rezultat dla grafu 1
    int totalCycleLength = result.totalLength;
    std::cout << "Total cycle length for graph 1: " << totalCycleLength << '\n';

    for (int i=0; i < graph.size(); i++) {
        for (int j=0; j < graph[0].size(); j++) {
            if ((graph[i][j]) != 0){
                std::cout << "vertices " << i << " " << j << '\n';
            }
        }
    }

    // oblicz ilość wierzchołków w drugim grafie
    numGraphRows = numRows - numGraphRows;

    // stwórz drugi graf
    result = GraphBuilder::buildGraph(distanceMatrix, isInGraph, numGraphRows);

    // pobierz dane dla drugiego grafu
    graph = result.graph;
    isInGraph = result.isInGraph;
    totalCycleLength = result.totalLength;

    // wyświetl rezultat dla grafu 2
    std::cout << "Total cycle length for graph 2: " << totalCycleLength << '\n';

    for (int i=0; i < graph.size(); i++) {
        for (int j=0; j < graph[0].size(); j++) {
            if ((graph[i][j]) != 0){
                std::cout << "vertices " << i << " " << j << '\n';
            }
        }
    }

    return 0;
}
