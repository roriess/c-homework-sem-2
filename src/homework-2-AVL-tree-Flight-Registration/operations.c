#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELENGTH 100
#define MAXKEYLENGTH 10
#define MAXNAMELENGTH 90

// структура узла АВЛ-дерева
typedef struct Node {
    char* key;
    char* airportName;
    struct Node* leftNode;
    struct Node* rightNode;
    int height; // разница высот левого и правого узла
} Node;

// структура АВЛ-дерева
typedef struct AVLTree {
    Node* root;
    unsigned int airportCount;
} AVLTree;


unsigned int getAirportCount(const AVLTree* tree) {
    return tree->airportCount;
}

static Node* createNode(const char* key, const char* name)
{
    Node* node = malloc(sizeof(Node));
    if (node == NULL) return NULL;

    node->key = malloc(strlen(key) + 1);
    node->airportName = malloc(strlen(name) + 1);

    if (node->key == NULL || node->airportName == NULL) {
        free(node->key);
        free(node->airportName);
        free(node);
        return NULL;
    }

    memcpy(node->key, key, strlen(key) + 1);
    memcpy(node->airportName, name, strlen(name) + 1);

    node->leftNode = NULL;
    node->rightNode = NULL;
    node->height = 1;

    return node;
}

AVLTree* createAVLTree(void)
{
    AVLTree* tree = malloc(sizeof(AVLTree));
    if (tree == NULL) return NULL;

    tree->root = NULL;
    tree->airportCount = 0;

    return tree;
}

static int getHeight(Node* node)
{
    return node ? node->height : 0;
}

static void updateHeight(Node* node)
{
    if (!node) return;

    int leftH = getHeight(node->leftNode);
    int rightH = getHeight(node->rightNode);
    node->height = 1 + (leftH > rightH ? leftH : rightH);
}

static Node* rotateLeft(Node* a)
{
    if (!a) return NULL;
    Node* b = a->rightNode;
    if (!b) return a;
    Node* c = b->leftNode;

    b->leftNode = a;
    a->rightNode = c;

    updateHeight(a);
    updateHeight(b);

    return b;
}

static Node* rotateRight(Node* a)
{
    Node* b = a->leftNode;
    Node* c = b->rightNode;

    b->rightNode = a;
    a->leftNode = c;

    updateHeight(a);
    updateHeight(b);

    return b;
}

static int getBalance(Node* node)
{
    return node ? getHeight(node->leftNode) - getHeight(node->rightNode) : 0;
}

static Node* rotateLeftRight(Node* node) {
    node->leftNode = rotateLeft(node->leftNode);
    return rotateRight(node);
}

static Node* rotateRightLeft(Node* node) {
    node->rightNode = rotateRight(node->rightNode);
    return rotateLeft(node);
}

static Node* balance(Node* node)
{
    if (node == NULL) return NULL;

    int balance = getBalance(node);

    if (balance > 1) {
        if (getBalance(node->leftNode) < 0)
            return rotateLeftRight(node);
        return rotateRight(node);
    }

    if (balance < -1) {
        if (getBalance(node->rightNode) > 0)
            return rotateRightLeft(node);
        return rotateLeft(node);
    }
    return node;
}

static Node* addNode(Node* root, const char* key, const char* name) // NOLINT(misc-no-recursion)
{
    if (root == NULL)
        return createNode(key, name);

    int cmp = strcmp(key, root->key);
    if (cmp < 0) {
        root->leftNode = addNode(root->leftNode, key, name);
    } else if (cmp > 0) {
        root->rightNode = addNode(root->rightNode, key, name);
    } else {
        return root;
    }

    updateHeight(root);
    return balance(root);
}

AVLTree* loadAirports(AVLTree* tree)
{
    if (tree == NULL) {
        tree = createAVLTree();
        if (tree == NULL) return NULL;
    }

    FILE* f = fopen("airports.txt", "r");
    if (!f) {
        quit(tree);
        return NULL;
    }
    char line[MAXLINELENGTH];
    char airportKey[MAXKEYLENGTH];
    char airportName[MAXNAMELENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%[^:]:%[^\n]", airportKey, airportName) == 2) {
            tree->root = addNode(tree->root, airportKey, airportName);
            count++;
        }
    }
    fclose(f);
    tree->airportCount = count;
    return tree;
}

static Node* findNode(Node* root, const char* key) // NOLINT(misc-no-recursion)
{
    if (root == NULL)
        return NULL;
    int cmp = strcmp(key, root->key);
    if (cmp < 0)
        return findNode(root->leftNode, key);
    if (cmp > 0)
        return findNode(root->rightNode, key);
    return root;
}

static Node* minValueNode(Node* node)
{
    Node* current = node;
    while (current && current->leftNode)
        current = current->leftNode;
    return current;
}

static Node* deleteNode(Node* root, const char* key) // NOLINT(misc-no-recursion)
{
    if (root == NULL)
        return NULL;

    int cmp = strcmp(key, root->key);
    if (cmp < 0) {
        root->leftNode = deleteNode(root->leftNode, key);
    } else if (cmp > 0) {
        root->rightNode = deleteNode(root->rightNode, key);
    } else {
        if (root->leftNode == NULL) {
            Node* temp = root->rightNode;
            free(root->key);
            free(root->airportName);
            free(root);
            return temp;
        } else if (root->rightNode == NULL) {
            Node* temp = root->leftNode;
            free(root->key);
            free(root->airportName);
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->rightNode);
        free(root->key);
        free(root->airportName);
        root->key = malloc(strlen(temp->key) + 1);
        root->airportName = malloc(strlen(temp->airportName) + 1);
        memcpy(root->key, temp->key, strlen(temp->key) + 1);
        memcpy(root->airportName, temp->airportName, strlen(temp->airportName));
        root->rightNode = deleteNode(root->rightNode, temp->key);
    }

    updateHeight(root);
    return balance(root);
}

static void saveNode(FILE* f, Node* node) // NOLINT(misc-no-recursion)
{
    if (node) {
        saveNode(f, node->leftNode);
        fprintf(f, "%s:%s\n", node->key, node->airportName);
        saveNode(f, node->rightNode);
    }
}

char* findAirport(AVLTree* tree, const char* key)
{
    if (tree == NULL || tree->root == NULL) return NULL;
    Node* node = findNode(tree->root, key);
    if (node == NULL) return NULL;
    return node->airportName;
}

int addAirport(AVLTree* tree, char* key, char* name)
{
    if (tree == NULL) return -1;
    
    if (findNode(tree->root, key) != NULL) return -1;

    tree->root = addNode(tree->root, key, name);
    tree->airportCount++;

    return 0;
}

int deleteAirport(AVLTree* tree, const char* key)
{
    if (tree == NULL || tree->root == NULL) return -1;
    if (findNode(tree->root, key) == NULL) return -1;
    tree->root = deleteNode(tree->root, key);
    tree->airportCount--;

    return 0;
}

unsigned int saveCurrentStatus(AVLTree* tree)
{
    if (tree == NULL || tree->root == NULL) return -1;
    FILE* f = fopen("airports.txt", "w");
    if (!f) return -1;
    saveNode(f, tree->root);
    fclose(f);
    return tree->airportCount;
}

static void freeSubtree(Node* node) // NOLINT(misc-no-recursion)
{
    if (node) {
        freeSubtree(node->leftNode);
        freeSubtree(node->rightNode);
        free(node->key);
        free(node->airportName);
        free(node);
    }
}

void quit(AVLTree* tree)
{
    if (tree) {
        freeSubtree(tree->root);
        free(tree);
        tree = NULL;
    }
}
