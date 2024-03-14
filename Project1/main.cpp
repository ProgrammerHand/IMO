#include <iostream>
#include <vector>
#include "file_management.h"
#include "distance_calculation.h"

int main() {
    const char* file_path = "kroA100.tsp";
    
    // read node coordinates and calculate distances
    std::vector<Point> nodes = readNodeCoordinates(file_path);

    // create matrix of distances
    std::vector<std::vector<int>> distanceMatrix = calculateDistanceMatrix(nodes);

    // print distance matrix
    printDistanceMatrix(distanceMatrix);

    // save distance matrix to file
    saveDistanceMatrixToFile(distanceMatrix, "output.txt");

    return 0;
}