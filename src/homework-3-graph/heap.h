#pragma once

typedef struct HeapNode {
    int distance; // текущее расстояние до города
    int cityNumber; // номер города
    int state; // индекс столицы, от которой отсчитано distance
} HeapNode;

typedef struct Heap {
    HeapNode* nodes;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity);

void pushHeap(Heap* heap, int distance, int cityNumber, int state);

HeapNode popHeap(Heap* heap);

int emptyHeap(Heap* heap);

void freeHeap(Heap* heap);
