//
// Created by samik on 2/2/2020.
//

#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <string>
#include <algorithm>
#include <iostream>
#include "constructGraph.h"


class Graph{
    vector<vector<int>> adjList;
    vector<bool> visited; /** tracks if a node has previously been visited */
    vector<int> entryTime; /** tracks the entry time of each node */
    vector<int> exitTime; /** tracks the exit time of each node */
    vector<int> parent; /** tracks the parent of each node / vertex */
    vector<string> state; /** Takes values: "undiscovered", "discovered", "processed" */
    bool isDirected;
    int time = 0;

public:
    Graph(int n, vector<vector<int>> &edges, bool isDirected) {

        /** According to the isDirected flag, call the appropriate graph construction function */
        adjList = isDirected ? adjListDirectedUnweighted(edges, n) : adjListUndirectedUnweighted(edges, n);

        /** According to number of nodes, initialize the class members */
        visited.resize(n, false);
        entryTime.resize(n, 0);
        exitTime.resize(n, 0);
        parent.resize(n, -1);
        state.resize(n, "undiscovered");
        this->isDirected = isDirected;
    }

    void DFS(int at) {
        visited[at] = true;
        state[at] = "discovered";

        time++;
        entryTime[at] = time + 1;

        for(auto &to: adjList[at]) {
            if (state[to] == "undiscovered") {
                parent[to] = at;
                DFS(to);
            }
        }
        state[at] = "processed";

        time++;
        exitTime[at] = time;

    }

    string findPath(int start, int end) {
        string path = "";
        int tempParent = this->parent[end];

        while (tempParent != -1) {
            path.push_back(tempParent - '0');
            tempParent = parent[tempParent];
        }
        reverse(path.begin(), path.end());
        return path;
    }

    // Detect cycle in an undirected graph
    bool hasCycle(int at, int parent) {
        visited[at] = true;

        for (auto &to: adjList[at]) {
            // In an undirected graph, parent is connected to child and vice versa.
            // This is not considered as a cycle in an undirected graph, rather this is a property
            // The first check in the below if ensures that
            if ((visited[to] && parent != to) || (!visited[to] && hasCycle(to, at)))
                cout << findPath(at, to) << endl;
                return true;
        }

        return false;
    }

    int getNoOfDescendants(int at) {
        return (exitTime[at] - entryTime[at]) / 2;
    }


};

#endif //GRAPHS_GRAPH_H
