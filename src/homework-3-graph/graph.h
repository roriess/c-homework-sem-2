#pragma once

#include <stdio.h>

typedef struct Edge {
    int to;
    int len;
} Edge;

typedef struct Graph {
    int cityCount;
    int roadCount;
    Edge** adj; // динамический массив списков смежности
    int* degree; // массив степеней вершин
} Graph;

Graph* createGraph(int cityCount);

void addEdgeToGraph(Graph* graph, int city1, int city2, int len);

Graph* readGraph(FILE* file);

void freeGraph(Graph* graph);