//
// Created by samik on 1/9/2020.
//

#ifndef GRAPHS_TOPOLOGICALSORT_H
#define GRAPHS_TOPOLOGICALSORT_H

#include <vector>
#include "constructGraph.h"

using namespace std;

/*
 * Start DFS at any node that is not visited
 * Explore its unvisited neighbours
 * Once done exploring the neighbors, add that node to the ordering list from behind
 * Decrement i
 * */

class topologicalSort {

public:
    int n;
    vector<int> ordering;
    vector<bool> visited;
    int i;

    topologicalSort(vector<vector<int>> edges, int n) {

        // Use the below edges and number of nodes to directly use topological sort

        /*vector<vector<int>> edges = {{2, 0}, {2, 1}, {1, 3}, {0, 3}, {3, 6}, {3, 7}, {4, 0}, {4, 3}, {4, 5}, {5, 10},
                                     {5, 9}, {6, 8}, {7, 8}, {7, 9}, {9, 12}, {9, 11}, {10, 9}};
        int n = 13;*/

        this->n = n;
        vector<vector<int>> adjList = adjListDirectedUnweighted(edges, n);
        ordering.resize(n, -1);
        visited.resize(n, false);
        i = n - 1;

        for (int at = 0; at < n; at++) {
            if (visited[at] != true) {
                DFS(adjList, at);
            }
        }

        for (auto &j: ordering) {
            cout << j << " ";
        }
        cout << endl;
    }

    void DFS(vector<vector<int>> &adjList, int curr) {
        visited[curr] = true;

        vector<int> edges = adjList.at(curr);
        for (auto &edge: edges) {
            if (visited[edge] != true) {
                DFS(adjList, edge);
            }
        }
        ordering[i] = curr;
        i--;
    }
};


#endif //GRAPHS_TOPOLOGICALSORT_H
