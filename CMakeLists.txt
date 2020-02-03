cmake_minimum_required(VERSION 3.15)
project(Graphs)

set(CMAKE_CXX_STANDARD 17)

add_executable(Graphs main.cpp searchAlgorithms.h DijkstrasShortestPathAdjacencyList.h constructGraph.h hasCycleInADirectedGraph.h hasCycleInAnUndirectedGraph.h UnionFind.h topologicalSort.h BellmanFordEdgeList.h checkIfBiPartite.h findBridgesAndArticulationPoints.h)