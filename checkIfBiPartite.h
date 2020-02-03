//
// Created by samik on 1/21/2020.
//

#ifndef GRAPHS_CHECKIFBIPARTITE_H
#define GRAPHS_CHECKIFBIPARTITE_H

#include <vector>
#include "constructGraph.h"
using namespace std;

string complement(vector<string> &color, int x) {
    if(color[x] == "White") return "black";
    else if (color[x] == "Black") return "white";

    return "Uncolored";
}

void bfs(vector<vector<int>> &adjList, int parent, vector<string> &color, vector<bool> &discovered) {

    queue<int> q;
    q.push(parent);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for(auto &p: adjList[curr]) {
            if (color[curr] == color[p]){
                cout << "Graph is not bipartite" << endl;
                return;
            } else if (discovered[p] == false) {
                discovered[p] = true;
                color[p] = complement(color, curr);
                q.push(p);
            }
        }
    }

}

/**
 * Call the below 'isBiPartite' function directly from main initialize graph from edge list
 */


void isBiPartite() {

    vector<vector<int>> edges = {{1, 2}, {1, 5}, {1, 6}, {2, 3}, {5, 4}, {3, 4}};
    int n = 6;

    vector<bool> discovered (n + 1, false);
    vector<string> color (n + 1, "Uncolored");
    vector<vector<int>> adjList = adjListUndirectedUnweighted(edges, n);

    for(int parent = 1; parent <= n; parent++) {
        if (discovered[parent] == false) {
            color[parent] = "White";
            discovered[parent] = true;
            bfs(adjList, parent, color, discovered);
        }
    }
}

#endif //GRAPHS_CHECKIFBIPARTITE_H
