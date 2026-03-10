#pragma once

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

// загрузка аэропортов в АВЛ-дерево
int loadAirports();

// нахождение аэропорта в дереве по iata_code
void findAirport(char key);

// добавление аэропорта в дерево по iata_code и name
void addAirport(char key, char name);

// удаление аэропорта по iata_code
void deleteAirport(char key);

// сохранение текущего состояния в airports.txt
void saveCurrentStatus();

// завершение работы программы
void quit();
