#include "operations.h"
#include "tests.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reset()
{
    quit();
    tree = createAVLTree();
    if (!tree) {
        printf("Ошибка: не удалось создать дерево.\n");
        exit(1);
    }
}

void testAddOneNode()
{
    reset();

    addAirport("SVO:Sheremetyevo International Airport");
    findAirport("SVO");
    assert(tree->airportCount == 1);
}

void testAddMultipleNode()
{
    reset();

    addAirport("C:Charlie");
    addAirport("A:Alpha");
    addAirport("B:Bravo");
    addAirport("D:Delta");
    addAirport("E:Echo");

    findAirport("A");
    findAirport("B");
    findAirport("C");
    findAirport("D");
    findAirport("E");
    assert(tree->airportCount == 5);
}

void testAddDuplicateNode()
{
    reset();

    addAirport("SVO:Sheremetyevo");
    addAirport("SVO:Sheremetyevo");
    assert(tree->airportCount == 1);
}

void testDeleteExistingNode()
{
    reset();

    addAirport("SVO:Sheremetyevo");
    addAirport("LED:Pulkovo");

    findAirport("SVO");
    deleteAirport("SVO");

    findAirport("SVO");
    findAirport("LED");
    assert(tree->airportCount == 1);
}

void testDeleteNonexistentNode()
{
    reset();

    addAirport("LED:Pulkovo");
    deleteAirport("SVO");
    assert(tree->airportCount == 1);
}

void testDeleteWithTwoChildren()
{
    reset();

    addAirport("B:Bravo");
    addAirport("A:Alpha");
    addAirport("C:Charlie");
    addAirport("D:Delta");
    addAirport("E:Echo");

    findAirport("C");
    deleteAirport("C");

    findAirport("C");

    findAirport("A");
    findAirport("B");
    findAirport("D");
    findAirport("E");

    assert(tree->airportCount == 4);
}

void testSaveFile()
{
    reset();

    addAirport("SVO:Sheremetyevo");
    addAirport("LED:Pulkovo");
    saveCurrentStatus();

    quit();
    tree = createAVLTree();
    int loaded = loadAirports();
    assert(loaded == 2);
    findAirport("SVO");
    findAirport("LED");
}

int test()
{
    testAddOneNode();
    testAddMultipleNode();
    testAddDuplicateNode();
    testDeleteExistingNode();
    testDeleteNonexistentNode();
    testDeleteWithTwoChildren();
    testSaveFile();

    quit();
    return 0;
}
