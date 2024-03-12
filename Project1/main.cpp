#include <iostream>
#include <vector>
#include "file_management.h"
#include "distance_calculation.h"
#include "cycle_expansion.h"
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

    // Example distance matrix
    //std::vector<std::vector<int>> distanceMatrix = {
    //    {0, 3, 5, 6, 9},
    //    {3, 0, 2, 7, 1},
    //    {5, 2, 0, 4, 8},
    //    {6, 7, 4, 0, 10},
    //    {9, 1, 8, 10, 0}
    //};


    // Build the graph using the GraphBuilder class
    int numRows = distanceMatrix.size();
    int numGraphRows = numRows / 2 + (numRows % 2);
    std::cout << "numGraphRows" << numGraphRows << '\n';
    std::vector<bool> isInGraph(numRows, false);

    Result result = GraphBuilder::buildGraph(distanceMatrix, isInGraph, numGraphRows);

    std::vector<std::vector<int>> graph = result.graph;
    isInGraph = result.isInGraph;

    for (int i=0; i < graph.size(); i++){
        for (int j=0; j < graph[0].size(); j++) {
            if ((graph[i][j]) != 0){
                std::cout << "graf " << i << " " << graph[i][j] << '\n';
            }
        }
    }

    numGraphRows = numRows - numGraphRows;

    result = GraphBuilder::buildGraph(distanceMatrix, isInGraph, numGraphRows);

    graph = result.graph;

    for (int i=0; i < graph.size(); i++){
        for (int j=0; j < graph[0].size(); j++) {
            if ((graph[i][j]) != 0){
                std::cout << "graf " << i << " " << graph[i][j] << '\n';
            }
        }
    }

    return 0;
}