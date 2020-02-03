//
// Created by samik on 1/8/2020.
//

#ifndef GRAPHS_CONSTRUCTGRAPH_H
#define GRAPHS_CONSTRUCTGRAPH_H

#include <vector>
using namespace std;

// Functions for constructing different adjacency Lists
vector<vector<int>> adjListUndirectedUnweighted(const vector<vector<int>> &edges, int numOfNodes) {

    vector<vector<int>> adjList(numOfNodes + 1, vector<int>());

    for(const vector<int> &i: edges) {
        adjList.at(i[0]).push_back(i[1]);
        adjList.at(i[1]).push_back(i[0]);
    }

    return adjList;
}

vector<vector<int>> adjListDirectedUnweighted(const vector<vector<int>> &edges, int numOfNodes) {

    vector<vector<int>> adjList(numOfNodes, vector<int>());

    for(const vector<int> &i: edges) {
        adjList.at(i[0]).push_back(i[1]);
    }

    return adjList;
}

#endif //GRAPHS_CONSTRUCTGRAPH_H
