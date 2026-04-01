#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* createGraph(int cityCount) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->cityCount = cityCount;
    graph->roadCount = 0;
    graph->adj = (Edge**)malloc(cityCount * sizeof(Edge*));
    graph->degree = (int*)calloc(cityCount, sizeof(int));

    for (int i = 0; i < cityCount; i++)
        graph->adj[i] = NULL;

    return graph;
}

void addEdgeToGraph(Graph* graph, int city1, int city2, int len) {
    graph->degree[city1]++;
    graph->degree[city2]++;
    graph->roadCount++;

    graph->adj[city1] = (Edge*)realloc(graph->adj[city1], graph->degree[city1] * sizeof(Edge));
    graph->adj[city2] = (Edge*)realloc(graph->adj[city2], graph->degree[city2] * sizeof(Edge));

    graph->adj[city1][graph->degree[city1] - 1].to = city2;
    graph->adj[city1][graph->degree[city1] - 1].len = len;

    graph->adj[city2][graph->degree[city2] - 1].to = city1;
    graph->adj[city2][graph->degree[city2] - 1].len = len;
}

Graph* readGraph(FILE* file) {
    int n, m;
    fscanf(file, "%d %d", &n, &m);

    Graph* graph = createGraph(n);

    for (int i = 0; i < m; i++) {
        int city1, city2, len;
        fscanf(file, "%d %d %d", &city1, &city2, &len);
        city1--;
        city2--;
        addEdgeToGraph(graph, city1, city2, len);
    }
    return graph;
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->cityCount; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph->degree);
    free(graph);
}
