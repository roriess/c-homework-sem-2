#pragma once

// очищение и создание нового дерева для тестов
void reset(void);

// добаление одного узла в дерево
void testAddOneNode(void);

// добавление нескольких узлов в дерево
void testAddMultipleNode(void);

// добавление двух одинаковых узлов
void testAddDuplicateNode(void);

// попытка удалить существующий узел
void testDeleteExistingNode(void);

// попытка удалить несуществующий узел
void testDeleteNonexistentNode(void);

// попытка удалить узел с левым и правым потомком
void testDeleteWithTwoChildren(void);

// сохранение данных в файл
void testSaveFile(void);

// запуск всех тестов
int testTree(void);
