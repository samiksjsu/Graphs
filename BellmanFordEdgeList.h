//
// Created by samik on 1/9/2020.
//

#ifndef GRAPHS_BELLMANFORDEDGELIST_H
#define GRAPHS_BELLMANFORDEDGELIST_H

#include <vector>
#include <limits>
#include <iostream>

using namespace std;
class BellmanFordEdgeList {

    /**
     * Just create an object of the above class and call the main method using . operator.
     * */

public:
    class Edge{

    public:
        int from, to;
        double cost;

        Edge(int from, int to, double cost) : from {from}, to {to}, cost {cost} {}
    };

    /**
   * An implementation of the Bellman-Ford algorithm. The algorithm finds the shortest path between
   * a starting node and all other nodes in the graph. The algorithm also detects negative cycles.
   * If a node is part of a negative cycle then the minimum cost for that node is set to
   * Double.NEGATIVE_INFINITY.
   *
   * @param edges - An edge list containing directed edges forming the graph
   * @param V - The number of vertices in the graph.
   * @param start - The id of the starting node
   */

    vector<double> bellmanFord(vector<Edge> edges, int V, int start) {

        vector<double> dist (V, numeric_limits<double>::infinity());
        dist[start] = 0;

        /**
         * Only in the worst case does it take V-1 iterations for the Bellman-Ford
         * algorithm to complete. Another stopping condition is when we're unable to
         * relax an edge, this means we have reached the optimal solution early.
         */

        bool relaxedAnEdge = true;

        for (int v = 0; v < V - 1 && relaxedAnEdge; v++) {
            relaxedAnEdge = false;
            for (Edge edge : edges) {
                if (dist[edge.from] + edge.cost < dist[edge.to]) {
                    dist[edge.to] = dist[edge.from] + edge.cost;
                    relaxedAnEdge = true;
                }
            }
        }


        /**
         * Run algorithm a second time to detect which nodes are part
        of a negative cycle. A negative cycle has occurred if we
        can find a better path beyond the optimal solution.
         */

        relaxedAnEdge = true;
        for (int v = 0; v < V - 1 && relaxedAnEdge; v++) {
            relaxedAnEdge = false;
            for (Edge edge : edges) {
                if (dist[edge.from] + edge.cost < dist[edge.to]) {
                    dist[edge.to] = numeric_limits<double>::infinity();
                    relaxedAnEdge = true;
                }
            }
        }

        return dist;
    }

    void run() {

        int E = 10, V = 9, start = 0;
        vector<Edge> edges;
        edges.emplace_back(0, 1, 1);
        edges.emplace_back(1, 2, 1);
        edges.emplace_back(2, 4, 1);
        edges.emplace_back(4, 3, -3);
        edges.emplace_back(3, 2, 1);
        edges.emplace_back(1, 5, 4);
        edges.emplace_back(1, 6, 4);
        edges.emplace_back(5, 6, 5);
        edges.emplace_back(6, 7, 4);
        edges.emplace_back(5, 7, 3);

        vector<double> d = bellmanFord(edges, V, start);

        for (int i = 0; i < V; i++)
            cout << "The cost to get node " << start << " to " << i << " is: " << d[i] << endl;

        // Output:
        // The cost to get from node 0 to 0 is 0.00
        // The cost to get from node 0 to 1 is 1.00
        // The cost to get from node 0 to 2 is -Infinity
        // The cost to get from node 0 to 3 is -Infinity
        // The cost to get from node 0 to 4 is -Infinity
        // The cost to get from node 0 to 5 is 5.00
        // The cost to get from node 0 to 6 is 5.00
        // The cost to get from node 0 to 7 is 8.00
        // The cost to get from node 0 to 8 is Infinity

    }
};


#endif //GRAPHS_BELLMANFORDEDGELIST_H
