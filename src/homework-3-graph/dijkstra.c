#include "dijkstra.h"
#include "heap.h"
#include <limits.h>
#include <stdlib.h>

void dijkstra(Graph* graph, int capitalsСount, int* capitals, int** distanceOut, int** ownerOut)
{
    int cityCount = graph->cityCount;

    int* distance = (int*)malloc(cityCount * sizeof(int)); // текущие расстояния до городов
    int* owner = (int*)malloc(cityCount * sizeof(int)); // индексы столиц (от 0 до сapitalCount-1), к которым относится каждый город

    for (int i = 0; i < cityCount; i++) {
        distance[i] = INT_MAX;
        owner[i] = -1;
    }

    Heap* heap = createHeap(cityCount);

    for (int i = 0; i < capitalsСount; i++) {
        int capital = capitals[i] - 1;
        distance[capital] = 0;
        owner[capital] = i;

        pushHeap(heap, 0, capital, i);
    }

    while (!emptyHeap(heap)) {
        HeapNode node = popHeap(heap);

        int dist = node.distance;
        int cityNumber = node.cityNumber;
        int state = node.state;

        if (dist > distance[cityNumber])
            continue;

        for (int i = 0; i < graph->degree[cityNumber]; i++) {
            int v = graph->adj[cityNumber][i].to;
            int w = graph->adj[cityNumber][i].len;
            int newDistance = dist + w;

            if (newDistance < distance[v]) {
                distance[v] = newDistance;
                owner[v] = state;
                pushHeap(heap, newDistance, v, state);
            }
        }
    }

    *distanceOut = distance;
    *ownerOut = owner;
    freeHeap(heap);
}
