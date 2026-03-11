#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELENGTH 100
#define MAXKEYLENGTH 10
#define MAXNAMELENGTH 90

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
    node->height = 1;

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

int getHeight(Node* node)
{
    return node ? node->height : 0;
}

void updateHeight(Node* node)
{
    if (node) {
        int leftH = getHeight(node->leftNode);
        int rightH = getHeight(node->rightNode);
        node->height = 1 + (leftH > rightH ? leftH : rightH);
    }
}

Node* rotateLeft(Node* a)
{
    Node* b = a->rightNode;
    Node* c = b->leftNode;

    b->leftNode = a;
    a->rightNode = c;

    if (c)
        c->parentNode = a;
    b->parentNode = a->parentNode;
    a->parentNode = b;

    updateHeight(a);
    updateHeight(b);

    return b;
}

Node* rotateRight(Node* a)
{
    Node* b = a->leftNode;
    Node* c = b->rightNode;

    b->rightNode = a;
    a->leftNode = c;

    if (c)
        c->parentNode = a;
    b->parentNode = a->parentNode;
    a->parentNode = b;

    updateHeight(a);
    updateHeight(b);

    return b;
}

int getBalance(Node* node)
{
    return node ? getHeight(node->leftNode) - getHeight(node->rightNode) : 0;
}

Node* balance(Node* node)
{
    if (node == NULL)
        return NULL;

    int bal = getBalance(node);

    if (bal > 1) {
        if (getBalance(node->leftNode) < 0) {
            node->leftNode = rotateLeft(node->leftNode);
            if (node->leftNode)
                node->leftNode->parentNode = node;
        }
        return rotateRight(node);
    }

    if (bal < -1) {
        if (getBalance(node->rightNode) > 0) {
            node->rightNode = rotateRight(node->rightNode);
            if (node->rightNode)
                node->rightNode->parentNode = node;
        }
        return rotateLeft(node);
    }
    return node;
}

Node* addNode(Node* root, const char* key, const char* name)
{
    if (root == NULL) // если дошли до низа дерева
        return createNode(key, name);

    int cmp = strcmp(key, root->key);
    if (cmp < 0) {
        root->leftNode = addNode(root->leftNode, key, name);
        if (root->leftNode)
            root->leftNode->parentNode = root;
    } else if (cmp > 0) {
        root->rightNode = addNode(root->rightNode, key, name);
        if (root->rightNode)
            root->rightNode->parentNode = root;
    } else {
        return root;
    }

    updateHeight(root);

    return balance(root);
}

AVLTree* tree = NULL;

int loadAirports(AVLTree* tree)
{
    if (tree == NULL)
        return -1;
    FILE* f = fopen("airports.txt", "r");
    if (f == NULL)
        return -1;

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
    return count;
}

Node* findNode(Node* root, const char* key)
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

Node* minValueNode(Node* node)
{
    Node* current = node;
    while (current && current->leftNode)
        current = current->leftNode;
    return current;
}

Node* deleteNode(Node* root, const char* key)
{
    if (root == NULL) {
        return NULL;
    }

    int cmp = strcmp(key, root->key);
    if (cmp < 0) {
        root->leftNode = deleteNode(root->leftNode);
        if (root->leftNode)
            root->leftNode->parentNode = root;
    } else if (cmp > 0) {
        root->rightNode = deleteNode(root->rightNode);
        if (root->rightNode)
            root->rightNode->parentNode = root;
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
        strcpy(root->key, temp->key);
        strcpy(root->airportName, temp->airportName);
        root->rightNode = deleteNode(root->rightNode, temp->key);
        if (root->rightNode)
            root->rightNode->parentNode = root;
    }

    updateHeight(root);
    return balance(root);
}

void saveNode(FILE* f, Node* node)
{
    if (node) {
        saveNode(f, node->leftNode);
        fprintf(f, "%s:%s\n", node->key, node->airportName);
        saveNode(f, node->rightNode);
    }
}

void findAirport(const char* key)
{
    if (tree == NULL || tree->root == NULL) {
        printf("База данных не загружена или пуста.\n");
        return;
    }
    Node* node = findNode(tree->root, key);
    if (node) {
        printf("%s → %s\n", key, node->airportName);
    } else {
        printf("Аэропорт с кодом '%s' не найден в базе.\n", key);
    }
}

void addAirport(const char* key, const char* name)
{
    if (tree == NULL) {
        tree = createAVLTree();
        if (tree == NULL) {
            return;
        }
    }
    tree->root = addNode(tree->root, key, name);
    tree->airportCount++;
    printf("Аэропорт '%s' добавлен в базу.\n", key);
}

void deleteAirport(const char* key)
{
    if (tree == NULL || tree->root == NULL) {
        return;
    }
    tree->root = deleteNode(tree->root, key);
    tree->airportCount--;

    printf("Аэропорт '%s' удалён из базы.\n", key);
}

void saveCurrentStatus()
{
    if (tree == NULL || tree->root == NULL) {
        printf("Нет данных для сохранения.\n");
        return;
    }
    FILE* f = fopen("airports.txt", "w");
    if (!f) {
        printf("Ошибка при открытии файла для записи.\n");
        return;
    }
    saveNode(f, tree->root);
    fclose(f);
    printf("База сохранена: %u аэропортов.\n", tree->airportCount);
}

void freeSubtree(Node* node)
{
    if (node) {
        freeSubtree(node->leftNode);
        freeSubtree(node->rightNode);
        free(node->key);
        free(node->airportName);
        free(node);
    }
}

void quit()
{
    if (tree) {
        freeSubtree(tree->root);
        free(tree);
        tree = NULL;
    }
    printf("Программа завершена.\n");
    exit(0);
}