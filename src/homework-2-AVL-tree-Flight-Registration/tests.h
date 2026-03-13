#pragma once

// очищение и создание нового дерева для тестов
void reset();

// добаление одного узла в дерево
void testAddOneNode();

// добавление нескольких узлов в дерево
void testAddMultipleNode();

// добавление двух одинаковых узлов
void testAddDuplicateNode();

// попытка удалить существующий узел
void testDeleteExistingNode();

// попытка удалить несуществующий узел
void testDeleteNonexistentNode();

// попытка удалить узел с левым и правым потомком
void testDeleteWithTwoChildren();

// сохранение данных в файл
void testSaveFile();

// запуск всех тестов
int test();
