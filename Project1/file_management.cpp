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
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == 'E') // Empty line or EOF
                break;

            std::istringstream istrstream(line);
            int node_number;
            int x, y;
            istrstream >> node_number >> x >> y;
            Point node;
            node.x = x;
            node.y = y;
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

void writeResultsToCSV(const std::vector<int>& tour1, double tour1Length, const std::vector<int>& tour2, double tour2Length, std::ofstream& outputFile) {
    for (int vertex : tour1) {
        outputFile << vertex << ",";
    }
    outputFile << std::endl;

    outputFile << tour1Length << std::endl;

    for (int vertex : tour2) {
        outputFile << vertex << ",";
    }
    outputFile << std::endl;

    outputFile << tour2Length << std::endl;
}