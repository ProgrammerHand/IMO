#include <iostream>
#include <vector>
#include "file_management.h"
#include "distance_calculation.h"

int main() {
    const char* file_path = "kroA100.tsp";
    
    // Read node coordinates and calculate distances
    std::vector<Point> nodes = readNodeCoordinates(file_path);

    // Create a matrix of distances
    std::vector<std::vector<int>> distanceMatrix = calculateDistanceMatrix(nodes);

    // Print the distance matrix
    printDistanceMatrix(distanceMatrix);

    // Save the distance matrix to a file
    saveDistanceMatrixToFile(distanceMatrix, "output.txt");

    return 0;
}