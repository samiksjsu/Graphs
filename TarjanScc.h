//
// Created by samik on 2/3/2020.
//

#ifndef GRAPHS_TARJANSCC_H
#define GRAPHS_TARJANSCC_H

#include <stack>
#include <climits>
#include <map>
#include <iostream>
#include "constructGraph.h"


/**
 * Strongly Connected components are basically self contained cycles.
 * So, basically we need to find the number of such group of cycles.
 *
 * Steps:
 *      1. Start DFS from any unvisited node.
 *      2. Continue pushing into stack and keep calling DFS for all unvisited neighbours.
 *      3. As soon as a cycle is found, backtrack and update the low values at the same time.
 *      4. We stop when we have found the main ancestor from where the this SCC started and basically got a back edge.
 *      5. We pop out all the value from stack till this starting point.
 *      6. Repeat for other neighbours is present.
 *
 *      Note: Stack is necessary because in a directed graph, the low values are dependent on the origin of the DFS.
 *            Hence, starting from different nodes will give different low link values for different nodes.
 *            So, we update low link values only if it is part of the current exploration and hence in the stack.
 *            Once a connected component is found, we pop all the values out and do not consider for other cycles.
 * */

class TarjanScc {

    int n;
    vector<vector<int>> adjList;

    int sccCount = 0, id = 0;
    vector<bool> onStack;
    vector<int> ids, lows;
    stack<int> stack;

    const int UNVISITED = -1;

    bool solved = false;
public:
    TarjanScc() {

        vector<vector<int>> edges {{6, 0}, {6, 2}, {3, 4}, {6, 4}, {2, 0}, {0, 1}, {4, 5},
                                   {5, 6}, {3, 7}, {7, 5}, {1, 2}, {7, 3}, {5, 0}};

        this->n = 8;
        this->adjList = adjListDirectedUnweighted(edges, n);

        onStack.resize(n, false);
        ids.resize(n, UNVISITED);
        lows.resize(n, INT_MAX);

        for (int i = 0; i < n; i++) if (ids[i] == UNVISITED) DFS(i);

        solved = true;
    }

    void DFS(int at) {
        stack.push(at);
        onStack[at] = true;
        ids[at] = lows[at] = id++;

        for (auto &to: adjList[at]) {
            if (ids[to] == UNVISITED) DFS(to);
            if (onStack[to]) lows[at] = min(lows[to], lows[at]);
        }

        if (ids[at] == lows[at]) {
            for(int node = stack.top(); ; node = stack.top()) {
                stack.pop();
                onStack[node] = false;
                if(node == at) break;
            }
            sccCount++;
        }
    }

    void getScc() {
        map<int, vector<int>> multiMap;
        for(int i = 0; i < n; i++) {
            multiMap[lows[i]].push_back(i);
        }

        cout << "No. of strongly connected components: " << this->sccCount << endl;
        for(auto itr = multiMap.begin(); itr != multiMap.end(); itr++) {
            cout << "[ ";
            for(auto &i: itr->second) {
                cout << i << " ";
            }
            cout << "] form part of a strongly connected component " << itr->first << endl;
        }
    }

};

#endif //GRAPHS_TARJANSCC_H
