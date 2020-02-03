//
// Created by Samik Biswas on 12-11-2019.
//

#ifndef GRAPHS_SEARCHALGORITHMS_H
#define GRAPHS_SEARCHALGORITHMS_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

// Different search algorithms
void BFS(vector<vector<int>> &nums, int i, int size) {
    queue<int> q;
    vector<int> visited(size, 0);

    cout << i << endl;
    visited.at(i) = 1;
    q.push(i);

    while (!q.empty()) {
        int element = q.front();
        q.pop();

        for (int j = 1; j < size; ++j) {
            if (nums.at(element).at(j) == 1 && visited.at(j) == 0) {
                cout << j << endl;
                visited.at(j) = 1;
                q.push(j);
            }
        }

    }
}

void DFS(vector<vector<int>> &nums, int i, int size) {
    static vector<int> visited (size, 0);

    if (visited[i] == 0) {
        cout << i << " ";
        visited[i] = 1;
        for (int j = 1; j < size; ++j) {
            if (nums.at(i).at(j) == 1) {
                DFS(nums, j, size);
            }
        }
    }
}

#endif //GRAPHS_SEARCHALGORITHMS_H
