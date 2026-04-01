#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dijkstra.h"

int main(int argc, char *argv[]) {
    FILE* input;
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "Cannot open file: %s\n", argv[1]);
            return 1;
        }
    }

    Graph* graph = readGraph(input);

    int capitalsСount;
    if (fscanf(input, "%d", &capitalsСount) != 1) {
        fprintf(stderr, "Failed to read k\n");
        return 1;
    }

    int* capitals = (int*)malloc(capitalsСount * sizeof(int));
    for (int i = 0; i < capitalsСount; i++) {
        if (fscanf(input, "%d", &capitals[i]) != 1) {
            fprintf(stderr, "Failed to read capital %d\n", i+1);
            return 1;
        }
    }

    int* distance;
    int* owner;
    dijkstra(graph, capitalsСount, capitals, &distance, &owner);

    int* counts = (int*)calloc(capitalsСount, sizeof(int));
    for (int i = 0; i < graph->cityCount; i++) {
        counts[owner[i]]++;
    }

    int** states = (int**)malloc(capitalsСount * sizeof(int*));
    for (int i = 0; i < capitalsСount; i++) {
        states[i] = (int*)malloc(counts[i] * sizeof(int));
    }

    int* index = (int*)calloc(capitalsСount, sizeof(int));
    for (int i = 0; i < graph->cityCount; i++) {
        int state = owner[i];
        states[state][index[state]++] = i + 1;
    }

    for (int i = 0; i < capitalsСount; i++) {
        printf("%d:", i + 1);
        for (int j = 0; j < counts[i]; j++) {
            printf(" %d", states[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < capitalsСount; i++) free(states[i]);
    free(states);
    free(index);
    free(counts);
    free(distance);
    free(owner);
    free(capitals);
    freeGraph(graph);

    return 0;
}
