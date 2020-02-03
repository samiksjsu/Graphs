//
// Created by samik on 1/28/2020.
//

#ifndef GRAPHS_FINDBRIDGESANDARTICULATIONPOINTS_H
#define GRAPHS_FINDBRIDGESANDARTICULATIONPOINTS_H

#include "constructGraph.h"

class findBridgesAndArticulationPoints {
    int id;
    vector<int> ids; // The entry point or time for each graph
    vector<int> lows; // The lowest reachable vertex from a particular node. Initially equal to the same node
    vector<int> articulationPoints; // Marks if a vertex is an articulation point
    vector<vector<int>> bridges;
    int n; // Number of nodes in the graph
    int rootNodeEdgeCount;

    vector<vector<int>> adjList;
    vector<bool> visited;

    void DFS(int root, int at, int parent) {

        if(parent == root) rootNodeEdgeCount++;

        visited[at] = true;
        ids[at] = lows[at] = id;
        id++;

        for(auto &to: adjList[at]) {
            if (to == parent) continue;

            if(visited[to] != true) {
                DFS(root, to, at);
            }
            lows[at] = min(lows[at], lows[to]);
            if (ids[at] <= lows[to]) {
                articulationPoints[at] = true;
                if (ids[at] < lows[to]) bridges.push_back(vector<int>{at, to});
            }

        }
    }

public:
    void main() {
        this->n = 9;
        this->id = 0;

        vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {2, 3}, {3, 4},
                                     {2, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 5}};


        /** Example 2*/
        // vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 4}};
        adjList = adjListUndirectedUnweighted(edges, n);
        visited.resize(n);

        // Adjust the ids vector according to the number of nodes
        ids.resize(n);
        fill(ids.begin(), ids.end(), 0);

        // Adjust the lows vector according to the number of nodes.
        lows.resize(n);
        for(int i = 0; i < n; i++) lows[i] = i;

        // Construct a vector containing all the nodes, to be marked if it is an articulation point
        articulationPoints.resize(n);

        for(int i = 0; i < n; i++) {
            if(visited[i] == false) {
                rootNodeEdgeCount = 0;
                DFS(i, i, -1);
                articulationPoints[i] = (rootNodeEdgeCount > 1);
            }
        }

        for(int i = 0; i < n; i++) {
            if(articulationPoints[i]) cout << i << endl;
        }
    }

};

#endif //GRAPHS_FINDBRIDGESANDARTICULATIONPOINTS_H
