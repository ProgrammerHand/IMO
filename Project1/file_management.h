#pragma once
#include <vector>
#include "distance_calculation.h"

std::vector<Point> readNodeCoordinates(const char* file_path);
void saveDistanceMatrixToFile(const std::vector<std::vector<int>>& distanceMatrix, const char* file_name);
void writeResultsToCSV(const std::vector<int>& tour1, double tour1Length, const std::vector<int>& tour2, double tour2Length, std::ofstream& outputFile);