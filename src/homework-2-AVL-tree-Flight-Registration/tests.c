#include "tests.h"
#include "operations.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AVLTree* resetTree(void)
{
    AVLTree* tree = createAVLTree();
    if (!tree) {
        printf("Ошибка: не удалось создать дерево.\n");
        return NULL;
    }
    return tree;
}

void testAddOneNode(void)
{
    AVLTree* tree = resetTree();

    addAirport(tree, "SVO", "Sheremetyevo International Airport");
    findAirport(tree, "SVO");
    assert(getAirportCount(tree) == 1);
    quit(tree);
}

void testAddMultipleNode(void)
{
    AVLTree* tree = resetTree();

    addAirport(tree, "C", "Charlie");
    addAirport(tree, "A", "Alpha");
    addAirport(tree, "B", "Bravo");
    addAirport(tree, "D", "Delta");
    addAirport(tree, "E", "Echo");

    findAirport(tree, "A");
    findAirport(tree, "B");
    findAirport(tree, "C");
    findAirport(tree, "D");
    findAirport(tree, "E");
    assert(getAirportCount(tree) == 5);
    quit(tree);
}

void testAddDuplicateNode(void)
{
    AVLTree* tree = resetTree();

    addAirport(tree, "SVO", "Sheremetyevo");
    addAirport(tree, "SVO", "Sheremetyevo");
    assert(getAirportCount(tree) == 1);
    quit(tree);
}

void testDeleteExistingNode(void)
{
    AVLTree* tree = resetTree();

    addAirport(tree, "SVO", "Sheremetyevo");
    addAirport(tree, "LED", "Pulkovo");

    findAirport(tree, "SVO");
    deleteAirport(tree, "SVO");

    findAirport(tree, "SVO");
    findAirport(tree, "LED");
    assert(getAirportCount(tree) == 1);
    quit(tree);
}

void testDeleteNonexistentNode(void)
{
    AVLTree* tree = resetTree();

    addAirport(tree, "LED", "Pulkovo");
    deleteAirport(tree, "SVO");
    assert(getAirportCount(tree) == 1);
    quit(tree);
}

void testDeleteWithTwoChildren(void)
{
    AVLTree* tree = resetTree();

    addAirport(tree, "B", "Bravo");
    addAirport(tree, "A", "Alpha");
    addAirport(tree, "C", "Charlie");
    addAirport(tree, "D", "Delta");
    addAirport(tree, "E", "Echo");

    findAirport(tree, "C");
    deleteAirport(tree, "C");

    findAirport(tree, "C");

    findAirport(tree, "A");
    findAirport(tree, "B");
    findAirport(tree, "D");
    findAirport(tree, "E");

    assert(getAirportCount(tree) == 4);
    quit(tree);
}

void testSaveFile(void)
{
    AVLTree* tree = resetTree();

    addAirport(tree, "SVO", "Sheremetyevo");
    addAirport(tree, "LED", "Pulkovo");
    saveCurrentStatus(tree);
    quit(tree);

    AVLTree* newTree = loadAirports(NULL);
    assert(getAirportCount(newTree) == 2);
    findAirport(newTree, "SVO");
    findAirport(newTree, "LED");
    quit(newTree);
}

int testTree(void)
{
    testAddOneNode();
    testAddMultipleNode();
    testAddDuplicateNode();
    testDeleteExistingNode();
    testDeleteNonexistentNode();
    testDeleteWithTwoChildren();
    testSaveFile();

    printf("Все тесты пройдены успешно!\n");
    return 0;
}
