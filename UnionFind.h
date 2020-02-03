//
// Created by samik on 1/8/2020.
//

#ifndef GRAPHS_UNIONFIND_H
#define GRAPHS_UNIONFIND_H

#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {

public:

    int size;
    int numComponents;
    vector<int> sz;
    vector<int> id;

    UnionFind(int n) {
        size = n;
        numComponents = n;

        // Now resize the sz and id vectors according to the number of nodes

        // Initially all individual nodes are single hence of size 1
        sz.resize(n);
        fill(sz.begin(), sz.end(), 1);

        // Initially all nodes are parent of itself, hence, id[i] = i
        id.resize(n);
        for (int i = 0; i < n; ++i) {
            id.at(i) = i;
        }


    }

    // The find function will give us the root of a particular node
    // Also, the path compression algo will run simultaneously
    int find(int p) {

        int root = p;

        // Go to the root of p
        while(root != id[root]) root = id[root];

        // Now if root != p we need path compression, from p till root
        while (p != root) {
            int next = id[p];
            id[p] = root;
            p = next;
        }

        return root;
    }

    bool connected(int p, int q) {
        return find(p) == find(q);
    }

    int componentSize(int p) {
        return sz[p];
    }

    void unify(int p, int q) {
        int root1 = find(p);
        int root2 = find(q);

        // root1 == root2 means elements are already in the same group
        // This property has 2 applications:
        //      i. To detect a cycle in an undirected graph
        //      ii. To find redundant components. Since they are forming a cycle, that means that edge is not needed, and hence redundant
        if (root1 == root2) return;

        if (sz[root1] > sz[root2]) {
            sz[root1] += sz[root2];
            id[root2] = root1;
        } else {
            sz[root2] += sz[root1];
            id[root1] = root2;
        }

        // At first, each node is a component on its own.
        // each unify will reduce the component count
        // This will be helpful to count Connected Components
        numComponents--;
    }
};




#endif //GRAPHS_UNIONFIND_H
