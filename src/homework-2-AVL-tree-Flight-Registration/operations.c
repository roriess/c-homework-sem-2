#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELENGTH 100
#define MAXKEYLENGTH 10
#define MAXNAMELENGTH 90

// // структура узла АВЛ-дерева
// typedef struct Node {
//     char* key;
//     char* airportName;
//     struct Node* leftNode;
//     struct Node* rightNode;
//     struct Node* parentNode;
//     int height; // разница высот левого и правого узла
// } Node;

// // структура АВЛ-дерева
// typedef struct AVLTree {
//     Node* root;
//     unsigned int airportCount;
// } AVLTree;

Node* createNode(const char* key, const char* name)
{
    Node* node = malloc(sizeof(Node));
    if (node == NULL)
        return NULL;

    node->key = malloc(strlen(key) + 1); // + 1 для "\0"
    node->airportName = malloc(strlen(name) + 1); // + 1 для "\0"

    if (node->key == NULL || node->airportName == NULL) {
        free(node->key);
        free(node->airportName);
        free(node);
        return NULL;
    }

    strcpy(node->key, key);
    strcpy(node->airportName, name);

    node->leftNode = NULL;
    node->rightNode = NULL;
    node->parentNode = NULL;
    node->height = 0;

    return node;
}

AVLTree* createAVLTree()
{
    AVLTree* tree = malloc(sizeof(AVLTree));
    if (tree == NULL)
        return NULL;

    tree->root = NULL;
    tree->airportCount = 0;

    return tree;
}

Node* addNode(Node* root, const char* key, const char* name)
{
    if (root == NULL) // если дошли до низа дерева
        root = createNode(key, name);

    if (strcmp(node->key, root->key) < 0) {
        root->leftNode = addNode(root->leftNode, key, name);
        if (root->leftNode)
            root->leftNode->parentNode = root;
    } else {
        root->rightNode = addNode(root->rightNode, key, name);
        if (root->rightNode)
            root->rightNode->parentNode = root;
    }
    return root;
}

int loadAirports()
{
    FILE* f = fopen("airports.txt", "r");
    if (f == NULL)
        return 0;

    AVLTree* tree = createAVLTree();

    char line[MAXLINELENGTH];

    // UTK:Utirik Airport
    char airportKey[MAXKEYLENGTH];
    char airportName[MAXNAMELENGTH];
    while (fgets(line, MAXLINELENGTH, f)) {
        sscanf(line, "%s %[^\n]", airportKey, airportName);
        Node* node = createNode(airportKey, airportName);
        if (tree->root == NULL) {
            tree->root = node;
            tree->airportCount = 1;
            continue;
        }
        // нужна функция для добавления узла в дерево
    }
    fclose(f);

    return tree->airportCount;
}

void findAirport(const char* key)
{
}

void addAirport(const char* key, const char* name)
{
}

void deleteAirport(const char* key)
{
}

void saveCurrentStatus()
{
}

void quit()
{
}
