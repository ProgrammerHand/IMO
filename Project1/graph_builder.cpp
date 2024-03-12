#include "graph_builder.h"
#include "cycle_expansion.h"
#include <iostream>
#include <limits>

Result GraphBuilder::buildGraph(const std::vector<std::vector<int>>& distanceMatrix, std::vector<bool> isInGraph, int numGraphRows) {
    int numRows = distanceMatrix.size();

    int numOfElems = 0;


    std::vector<std::vector<int>> graph(distanceMatrix.size(), std::vector<int>(distanceMatrix[0].size(), 0));

    int randomRowIndex = RandomElement::get_random_node(distanceMatrix);
    while (isInGraph[randomRowIndex]){
        randomRowIndex = RandomElement::get_random_node(distanceMatrix);
    }

    std::cout << "Random row index " << randomRowIndex << '\t';

    isInGraph[randomRowIndex] = true;
    numOfElems++;

    int closestNodeIndex = RandomElement::find_closest_node(distanceMatrix, randomRowIndex, isInGraph);

    graph[randomRowIndex][closestNodeIndex] = distanceMatrix[randomRowIndex][closestNodeIndex];
    graph[closestNodeIndex][randomRowIndex] = distanceMatrix[closestNodeIndex][randomRowIndex];
    isInGraph[closestNodeIndex] = true;
    numOfElems++;

    int thirdIndex = RandomElement::create_cycle(distanceMatrix, randomRowIndex, closestNodeIndex, isInGraph);

    graph[closestNodeIndex][thirdIndex] = distanceMatrix[closestNodeIndex][thirdIndex];
    graph[thirdIndex][closestNodeIndex] = distanceMatrix[thirdIndex][closestNodeIndex];
    graph[thirdIndex][randomRowIndex] = distanceMatrix[thirdIndex][randomRowIndex];
    graph[randomRowIndex][thirdIndex] = distanceMatrix[randomRowIndex][thirdIndex];
    isInGraph[thirdIndex] = true;
    numOfElems++;

    int maxDistance;
    int maxDistanceEdgeStart;
    int maxDistanceEdgeEnd;

    while (numOfElems <= numGraphRows) {
        std::cout << "While " << numOfElems << '\n';
        maxDistance = -1;
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++)

            if (graph[i][j] > maxDistance) {
                maxDistance = graph[i][j];
                maxDistanceEdgeStart = i;
                maxDistanceEdgeEnd = j;
            }
        }

        std::cout << "maxDistance is "  << maxDistance << " for edge " << maxDistanceEdgeStart << " and " << maxDistanceEdgeEnd << '\n';

        graph[maxDistanceEdgeStart][maxDistanceEdgeEnd] = 0;
        graph[maxDistanceEdgeEnd][maxDistanceEdgeStart] = 0;

        int newNode = RandomElement::create_cycle(distanceMatrix, maxDistanceEdgeStart, maxDistanceEdgeEnd, isInGraph);
        
        std::cout << "Random row index " << newNode << '\t';

        graph[maxDistanceEdgeStart][newNode] = distanceMatrix[maxDistanceEdgeStart][newNode];
        graph[newNode][maxDistanceEdgeStart] = distanceMatrix[newNode][maxDistanceEdgeStart];
        graph[newNode][maxDistanceEdgeEnd] = distanceMatrix[newNode][maxDistanceEdgeEnd];
        graph[maxDistanceEdgeEnd][newNode] = distanceMatrix[maxDistanceEdgeEnd][newNode];
        isInGraph[newNode] = true;

        numOfElems++;
    }

    Result result;
    result.graph = graph;
    result.isInGraph = isInGraph;

    return result;
}
