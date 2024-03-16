#include <iostream>
#include <vector>
#include "file_management.h"
#include "distance_calculation.h"
#include "greedy_expansion_knn.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <fstream>


int main() {
    const char* file_path = "kroA100.tsp";
    
    // reading node coordinates and calculating distances
    std::vector<Point> nodes = readNodeCoordinates(file_path);

    // creating a matrix of distances
    std::vector<std::vector<int>> distanceMatrix = calculateDistanceMatrix(nodes);

    // // print distance matrix
    // printDistanceMatrix(distanceMatrix);

    // // save distance matrix to file
    // saveDistanceMatrixToFile(distanceMatrix, "output.txt");

    // size of each tour
    int tourSize = 50;

    // greedy algorithm with random starting vertices for two independent tours
    std::ofstream outputFile("results.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    for (int i = 0; i < 100; ++i) {
        TwoTours result = greedyAlgorithmRandomStart(distanceMatrix, tourSize);
        int tour1Length = calculateTourLength(result.tour1.vertices, distanceMatrix);
        int tour2Length = calculateTourLength(result.tour2.vertices, distanceMatrix);
        writeResultsToCSV(result.tour1.vertices, tour1Length, result.tour2.vertices, tour2Length, outputFile);
    }
    // // resulting tours print
    // std::cout << "Resulting Tour 1: ";
    // for (int vertex : result.tour1.vertices) {
    //     std::cout << vertex << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "\nTour 1 Length: " << calculateTourLength(result.tour1.vertices, distanceMatrix) << std::endl;

    // std::cout << "\nResulting Tour 2: ";
    // for (int vertex : result.tour2.vertices) {
    //     std::cout << vertex << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "\nTour 2 Length: " << calculateTourLength(result.tour2.vertices, distanceMatrix) << std::endl;

    return 0;
}