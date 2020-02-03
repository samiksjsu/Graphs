#include <iostream>
#include "constructGraph.h"
#include "topologicalSort.h"
#include "BellmanFordEdgeList.h"
#include "hasCycleInADirectedGraph.h"
#include "DijkstrasShortestPathAdjacencyList.h"
#include "searchAlgorithms.h"
#include "checkIfBiPartite.h"
#include "findBridgesAndArticulationPoints.h"
using namespace std;

int main() {


    findBridgesAndArticulationPoints g1;
    g1.main();

    cout << "Hello" << endl;
}