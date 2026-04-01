#include "heap.h"
#include <stdlib.h>

Heap* createHeap(int capacity)
{
    Heap* heap = (Heap*)malloc(sizeof(Heap));

    heap->nodes = (HeapNode*)malloc(sizeof(HeapNode) * capacity);

    heap->size = 0;
    heap->capacity = capacity;

    return heap;
}

static void swap(HeapNode* node1, HeapNode* node2)
{
    HeapNode tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
}

static void heapifyUp(Heap* heap, int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap->nodes[parent].distance <= heap->nodes[index].distance)
            break;

        swap(&heap->nodes[parent], &heap->nodes[index]);
        index = parent;
    }
}

static void heapifyDown(Heap* heap, int index)
{
    int left, right, smallest;

    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < heap->size && heap->nodes[left].distance < heap->nodes[smallest].distance)
            smallest = left;

        if (right < heap->size && heap->nodes[right].distance < heap->nodes[smallest].distance)
            smallest = right;

        if (smallest == index)
            break;

        swap(&heap->nodes[index], &heap->nodes[smallest]);
        index = smallest;
    }
}

void pushHeap(Heap* heap, int distance, int cityNumber, int state)
{
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->nodes = (HeapNode*)realloc(heap->nodes, sizeof(HeapNode) * heap->capacity);
    }

    heap->nodes[heap->size].distance = distance;
    heap->nodes[heap->size].cityNumber = cityNumber;
    heap->nodes[heap->size].state = state;
    heap->size++;

    heapifyUp(heap, heap->size - 1);
}

HeapNode popHeap(Heap* heap)
{
    HeapNode top = heap->nodes[0];
    heap->size--;
    heap->nodes[0] = heap->nodes[heap->size];

    heapifyDown(heap, 0);

    return top;
}

int emptyHeap(Heap* heap)
{
    return heap->size == 0;
}

void freeHeap(Heap* heap)
{
    free(heap->nodes);
    free(heap);
}
