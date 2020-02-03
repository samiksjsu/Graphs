//
// Created by samik on 1/8/2020.
//

#ifndef GRAPHS_HASCYCLEINANUNDIRECTEDGRAPH_H
#define GRAPHS_HASCYCLEINANUNDIRECTEDGRAPH_H

#include <vector>
#include <iostream>
#include "constructGraph.h"
using namespace std;

// Detect cycle in an undirected graph
bool hasCycle(vector<vector<int>> &adjList, int curr, vector<bool> &visited, int parent) {
    visited[curr] = true;

    for (int i = 0; i < adjList.at(curr).size(); i++) {
        int v = adjList.at(curr).at(i);

        // In an undirected graph, parent is connected to child and vice versa.
        // This is not considered as a cycle in an undirected graph, rather this is a property
        // The first check in the below if ensures that
        if ((visited[v] && parent != v) || (!visited[v] && hasCycle(adjList, v, visited, curr)))
            return true;
    }

    return false;
}

class hasCycleInAnUndirectedGraph {

public:
    hasCycleInAnUndirectedGraph(vector<vector<int>> &edges, int n) {
        vector<bool> visited (n, false);
        vector<vector<int>> adjList = adjListUndirectedUnweighted(edges, n);

        cout << hasCycle(adjList, 0, visited, -1) << endl;
    }
};


#endif //GRAPHS_HASCYCLEINANUNDIRECTEDGRAPH_H
