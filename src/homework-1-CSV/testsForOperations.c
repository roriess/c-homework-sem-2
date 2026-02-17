#include "operations.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void testReadText()
{
    FILE* f = fopen("test1.csv", "w");
    fprintf(f, "name,age\n");
    fprintf(f, "anna,25\n");
    fprintf(f, "ivan,30\n");
    fclose(f);

    Data* data = readText("test1.csv");
    assert(data != NULL);
    assert(data->linesCount == 3);
    assert(strcmp(data->data[0], "name,age") == 0);
    assert(strcmp(data->data[1], "anna,25") == 0);
    assert(strcmp(data->data[2], "ivan,30") == 0);

    for (int i = 0; i < data->linesCount; i++)
        free(data->data[i]);
    free(data->data);
    free(data);
    remove("test1.csv");

    data = readText("nofile.csv");
    assert(data == NULL);

    data = readText("empty.csv");
    assert(data == NULL || data->linesCount == 0);
    if (data) {
        free(data->data);
        free(data);
    }
    remove("empty.csv");
}

void testCountColumns()
{
    Data* data1 = malloc(sizeof(Data));
    char* lines1[] = { "a,b,c" };
    data1->data = lines1;
    data1->linesCount = 1;
    assert(countColumns(data1) == 3);
    free(data1);

    Data* data2 = malloc(sizeof(Data));
    char* lines2[] = { "" };
    data2->data = lines2;
    data2->linesCount = 1;
    assert(countColumns(data2) == 1);
    free(data2);
}

void testColumnWidth()
{
    Data* data = malloc(sizeof(Data));
    char* lines1[] = { "a,bb,ccc", "dddd,e,f", "g,hhhhhh,iii" };
    data->data = lines1;
    data->linesCount = 3;

    const int* widths = columnWidth(data);
    assert(widths[0] == 4);
    assert(widths[1] == 6);
    assert(widths[2] == 3);
    free((void*)widths);

    char* lines2[] = { ",,", "a,,", ",b,", ",,c" };
    data->data = lines2;
    data->linesCount = 4;

    widths = columnWidth(data);
    assert(widths[0] == 1);
    assert(widths[1] == 1);
    assert(widths[2] == 1);
    free((void*)widths);

    free(data);
}

void testTableWidth()
{
    Data* data = malloc(sizeof(Data));
    data->columnCount = 3;

    int spaces1[] = { 5, 10, 7 };
    assert(tableWidth(data, spaces1) == 22);

    int spaces2[] = { 0, 0, 0 };
    assert(tableWidth(data, spaces2) == 0);

    data->columnCount = 1;
    int spaces4[] = { 42 };
    assert(tableWidth(data, spaces4) == 42);

    free(data);
}

void testIsNumber()
{
    assert(isNumber("123") == 1);
    assert(isNumber("45.67") == 1);
    assert(isNumber("0") == 1);

    assert(isNumber("123,45") == 0);
    assert(isNumber("") == 0);
    assert(isNumber("12a") == 0);
}

void testAll()
{
    testReadText();
    testCountColumns();
    testColumnWidth();
    testTableWidth();
    testIsNumber();
}