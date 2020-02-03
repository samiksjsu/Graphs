#include <iostream>
#include "constructGraph.h"
#include "topologicalSort.h"
#include "BellmanFordEdgeList.h"
#include "hasCycleInADirectedGraph.h"
#include "DijkstrasShortestPathAdjacencyList.h"
#include "searchAlgorithms.h"
#include "checkIfBiPartite.h"
#include "findBridgesAndArticulationPoints.h"
#include "TarjanScc.h"
using namespace std;

int main() {


    TarjanScc t1;
    t1.getScc();

    cout << "Hello World" << endl;
}