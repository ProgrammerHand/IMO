#include "file_management.h"
#include <fstream>
#include <sstream>
#include <iostream>


std::vector<Point> readNodeCoordinates(const char* file_path) {
    std::ifstream file(file_path);
    std::vector<Point> nodes;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line) && line.find("NODE_COORD_SECTION") == std::string::npos);

        Point node;
        while (file >> node.x >> node.y) {
            nodes.push_back(node);
        }

        file.close();
    } else {
        std::cerr << "Error opening file: " << file_path << std::endl;
    }

    return nodes;
}

void saveDistanceMatrixToFile(const std::vector<std::vector<int>>& distanceMatrix, const char* file_name) {
    std::ofstream outputFile(file_name);
    if (outputFile.is_open()) {
        for (size_t i = 0; i < distanceMatrix.size(); ++i) {
            for (size_t j = 0; j < distanceMatrix[i].size(); ++j) {
                outputFile << distanceMatrix[i][j] << " ";
            }
            outputFile << std::endl;
        }
        outputFile.close();
        std::cout << "Output saved to '" << file_name << "'\n";
    } else {
        std::cerr << "Error creating output file.\n";
    }
}