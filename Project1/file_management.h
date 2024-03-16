#pragma once
#include <vector>
#include <string>
#include "distance_calculation.h"

std::vector<Point> readNodeCoordinates(const char* file_path);
void saveDistanceMatrixToFile(const std::vector<std::vector<int>>& distanceMatrix, const char* file_name);
void writeVerticesToFile(const std::vector<std::vector<int>>& graph, int totalCycleLength, const std::string& filename);