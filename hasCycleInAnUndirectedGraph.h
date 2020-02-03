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
bool hasCycle(vector<vector<int>> &adjList, int at, vector<bool> &visited, int parent) {
    visited[at] = true;

    for (auto &to: adjList[at]) {
        // In an undirected graph, parent is connected to child and vice versa.
        // This is not considered as a cycle in an undirected graph, rather this is a property
        // The first check in the below if ensures that
        if ((visited[to] && parent != to) || (!visited[to] && hasCycle(adjList, to, visited, at)))
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
