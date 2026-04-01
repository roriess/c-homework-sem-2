#pragma once
#include "graph.h"

// многокомпонентный алгоритм Дейкстры
// находит для каждого города ближайшую столицу и расстояние до неё
void dijkstra(Graph* graph, int capitalsСount, int* capitals, int** distanceOut, int** ownerOut);
