#pragma once

#include <stdio.h>

typedef struct AVLTree AVLTree;

// геттер для доступа к полю tree->airportCount, которое нужно тестам и main
unsigned int getAirportCount(const AVLTree* tree);

// создание дерева
AVLTree* createAVLTree(void);

// загрузка аэропортов в АВЛ-дерево
AVLTree* loadAirports(AVLTree* tree);

// нахождение аэропорта в дереве по iata_code
char* findAirport(AVLTree* tree, const char* key);

// добавление аэропорта в дерево по iata_code и name
int addAirport(AVLTree* tree, char* key, char* name);

// удаление аэропорта по iata_code
int deleteAirport(AVLTree* tree, const char* key);

// сохранение текущего состояния в airports.txt
unsigned int saveCurrentStatus(AVLTree* tree);

// завершение работы программы
void quit(AVLTree* tree);
