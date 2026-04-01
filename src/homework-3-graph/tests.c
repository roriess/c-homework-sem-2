#include "dijkstra.h"
#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void testTwoCapitals()
{
    Graph* graph = createGraph(3);

    addEdgeToGraph(graph, 0, 1, 1);
    addEdgeToGraph(graph, 1, 2, 1);

    int capitals[] = { 1, 3 };

    int* distance;
    int* owner;
    dijkstra(graph, 2, capitals, &distance, &owner);

    assert(owner[0] == 0);
    assert(owner[2] == 1);
    assert(owner[1] == 0 || owner[1] == 1);

    free(distance);
    free(owner);
    freeGraph(graph);
}

void testThreeCapitals()
{
    Graph* graph = createGraph(4);

    addEdgeToGraph(graph, 0, 1, 1);
    addEdgeToGraph(graph, 1, 2, 1);
    addEdgeToGraph(graph, 2, 3, 1);
    addEdgeToGraph(graph, 3, 0, 1);

    int capitals[] = { 1, 2, 3 };

    int* distance;
    int* owner;

    dijkstra(graph, 3, capitals, &distance, &owner);

    assert(owner[0] == 0);
    assert(owner[1] == 1);
    assert(owner[2] == 2);
    assert(owner[3] == 0 || owner[3] == 2);

    free(distance);
    free(owner);
    freeGraph(graph);
}

void testWeights()
{
    Graph* graph = createGraph(3);

    addEdgeToGraph(graph, 0, 1, 10);
    addEdgeToGraph(graph, 0, 2, 5);

    int capitals[] = { 1, 2 };

    int* distance;
    int* owner;

    dijkstra(graph, 2, capitals, &distance, &owner);

    assert(owner[0] == 0);
    assert(owner[1] == 1);
    assert(owner[2] == 0);

    free(distance);
    free(owner);
    freeGraph(graph);
}

int main()
{
    testTwoCapitals();
    testThreeCapitals();
    testWeights();
    return 0;
}
