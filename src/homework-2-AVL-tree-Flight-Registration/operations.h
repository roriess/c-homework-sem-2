#pragma once

#include <stdio.h>

// структура узла АВЛ-дерева
typedef struct Node {
    char* key;
    char* airportName;
    struct Node* leftNode;
    struct Node* rightNode;
    struct Node* parentNode;
    int height; // разница высот левого и правого узла
} Node;

// структура АВЛ-дерева
typedef struct AVLTree {
    Node* root;
    unsigned int airportCount;
} AVLTree;

// создание узла дерева
Node* createNode(const char* key, const char* name);

// создание дерева
AVLTree* createAVLTree();

// возвращает высоту узла. Если узла нет - то 0
int getHeight(Node* node);

// обновление высоты узла
void updateHeight(Node* node);

// левый малый поворот
Node* rotateLeft(Node* a);

// правый малый поворот
Node* rotateRight(Node* a);

// проверка баланса узла
int getBalance(Node* node);

// балансировка дерева
Node* balance(Node* node);

// добавление узла в обычное бин дерево поиска (без АВЛ свойств)
Node* addNode(Node* root, const char* key, const char* name);

// загрузка аэропортов в АВЛ-дерево
int loadAirports();

// нахождение узла по ключу
Node* findNode(Node* root, const char* key);

// нахлждение минимального узла
Node* minValueNode(Node* node);

// удаление узла
Node* deleteNode(Node* root, const char* key);

// сохранение узла в airports.txt
void saveNode(FILE* f, Node* node);

// нахождение аэропорта в дереве по iata_code
void findAirport(const char* key);

// добавление аэропорта в дерево по iata_code и name
void addAirport(const char* argument);

// удаление аэропорта по iata_code
void deleteAirport(const char* key);

// сохранение текущего состояния в airports.txt
void saveCurrentStatus();

// освобождение дерева
void freeSubtree(Node* node);

// завершение работы программы
void quit();
