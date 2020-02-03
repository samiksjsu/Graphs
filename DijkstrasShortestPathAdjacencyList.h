//
// Created by samik on 1/6/2020.
//

#ifndef GRAPHS_DIJKSTRASSHORTESTPATHADJACENCYLIST_H
#define GRAPHS_DIJKSTRASSHORTESTPATHADJACENCYLIST_H

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class DijkstrasShortestPathAdjacencyList {


public:

    // An edge class to represent a directed edge
    // between two nodes with a certain cost.
    class Edge {
    public:
        double cost;
        int from, to;

        Edge(int from, int to, double cost) : from{from}, to{to}, cost{cost} {}
    };

    // Node class to track the nodes to visit while running Dijkstra's
    // These nodes will be placed in the priority queue
    class Node {

    public:
        int id;
        double value;

        Node () : id {0}, value {0} {}
        Node(int id = 0, double value = 0) : id{id}, value{value} {}
    };

    int n; // number of nodes
    vector<double> dist; // distance of each node from the start node
    vector<int> prev; // for each node, this will track it's parent.
    vector<vector<Edge>> graph;


    DijkstrasShortestPathAdjacencyList(int n) : n{n} {
        createEmptyGraph();
    }

    void createEmptyGraph() {
        for (int i = 0; i < n + 1; i++) graph.emplace_back();
    }

    /**
   * Adds a directed edge to the graph.
   *
   * @param from - The index of the node the directed edge starts at.
   * @param to - The index of the node the directed edge end at.
   * @param cost - The cost of the edge.
   */
    void addEdge(int from, int to, double cost) {
        graph.at(from).emplace_back(from, to, cost);
    }

    vector<vector<Edge>> getGraph() {
        return graph;
    }

    vector<int> reconstructPath(int start, int end) {

        // First check if the bounds are withing range
        if (end < 0 || end > n) return vector<int>();
        if (start < 0 || start >= n) return vector<int>();

        // Run dijkstra's algorithm
        // This will fill the prev and dist vector
        double dist = dijkstra(start, end);

        vector<int> path;

        // If the end node was unreachable from the start node, dijkstra will return +infinity
        // So, in this case we cannot reconstruct the path. Hence we return an empty vector
        if (dist == numeric_limits<double>::infinity()) return path;

        // else, we reconstruct the path.
        // Note that, path starts from end and moves towards start.
        // But we need to provide start to end. Hence we reverse the path vector before returning
        for (int i = end; i != -1; i = prev.at(i)) {
            path.push_back(i);
        }

        reverse(path.begin(), path.end());

        return path;
    }

    struct compareValue {
        bool operator()(Node const &n1, Node const &n2) {
            // return "true" if "p1" is ordered
            // before "p2", for example:
            return n1.value > n2.value;
        }
    };

    // Run Dijkstra's algorithm on a directed graph to find the shortest path
    // from a starting node to an ending node. If there is no path between the
    // starting node and the destination node the returned value is set to be
    // numeric_limits<double> infinity()

    double dijkstra(int start, int end) {
        dist.resize(n + 1);
        fill(dist.begin(), dist.end(), numeric_limits<double>::infinity());
        dist.at(start) = 0;

        // Keep a priority queue of the next most promising node to visit.
        priority_queue<Node, vector<Node>, compareValue> pq;
        pq.emplace(start, 0);


        // Array used to track which nodes have already been visited.
        vector<bool> visited(n + 1, false);
        prev.resize(n + 1);
        fill(prev.begin(), prev.end(), -1);

        while (!pq.empty()) {
            Node node = pq.top();
            pq.pop();
            visited.at(node.id) = true;

            // We already found a better path before we got to
            // processing this node so we can ignore it.
            if (dist[node.id] < node.value) continue;

            vector<Edge> edges = graph.at(node.id);

            for(auto &edge: edges) {

                // You cannot get a shorter path by revisiting
                // a node you have already visited before.
                if (visited[edge.to]) continue;

                // Relax edge by updating minimum cost if applicable.
                int newDist = dist[edge.from] + edge.cost;

                if (newDist < dist[edge.to]) {
                    prev[edge.to] = edge.from;
                    dist[edge.to] = newDist;
                    pq.emplace(edge.to, newDist);
                }
            }

            // Once we've visited all the nodes spanning from the end
            // node we know we can return the minimum distance value to
            // the end node because it cannot get any better after this point.
            if (node.id == end) return dist[end];
        }

        // End node is unreachable
        return numeric_limits<double >::infinity();
    }

};


#endif //GRAPHS_DIJKSTRASSHORTESTPATHADJACENCYLIST_H
