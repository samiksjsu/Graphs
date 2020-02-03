//
// Created by samik on 1/8/2020.
//

#ifndef GRAPHS_HASCYCLEINADIRECTEDGRAPH_H
#define GRAPHS_HASCYCLEINADIRECTEDGRAPH_H

#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include "constructGraph.h"
using namespace std;

void reconstructPath(int curr, unordered_map<int, int> &parentMap) {

    int parent = curr;
    string path = "";

    path += curr + '0';
    path.push_back('>');
    path.push_back('-');


    while (parentMap[curr] != parent) {
        curr = parentMap[curr];
        path += curr + '0';
        path.push_back('>');
        path.push_back('-');
    }

    path += parent + '0';

    reverse(path.begin(), path.end());

    cout << path << endl;
}

// Detect cycle in a directed graph
bool hasCycle(vector<vector<int>> &adjList, int curr, vector<bool> &visited, vector<bool> &visiting, unordered_map<int, int> &parentMap) {
    visiting[curr] = true;

    for (int i = 0; i < adjList.at(curr).size(); ++i) {
        int v = adjList.at(curr).at(i);
        parentMap[v] = curr;

        if (visited[v] == true) continue;

        if (visiting[v]) {
            reconstructPath(v, parentMap);
            return true;
        }

        if (hasCycle(adjList, v, visited, visiting, parentMap)) {
            // reconstructPath(v, parentMap);
            return true;
        }
    }

    visiting[curr] = false;
    visited[curr] = true;

    return false;
}


class hasCycleInADirectedGraph{

public:
    hasCycleInADirectedGraph(vector<vector<int>> &edges, int n) {
        vector<bool> visited (n, false);
        vector<bool> visiting (n, false);
        vector<vector<int>> adjList = adjListDirectedUnweighted(edges, n);
        unordered_map<int, int> parentMap;
        cout << boolalpha;

        for (int i = 0; i < n; i++ ) {
            if (visited[i]) continue;
            if (hasCycle(adjList, i, visited, visiting, parentMap)) {
                cout << "There is a cycle in the graph" << endl;
                break;
            }
        }
    }

};

#endif //GRAPHS_HASCYCLEINADIRECTEDGRAPH_H
