#pragma once

#include <stdio.h>

typedef struct {
    char** data;
    int linesCount;
    int columnCount;
} Data;

// чтение данных из input.csv в массив указателей на строки
Data* readText(const char* fileName);

// подсчет кол-ва столбцов таблицы
int countColumns(Data* data);

// подсчет ширины столбцов
const int* columnWidth(Data* data);

// подсчет ширины таблицы
int tableWidth(Data* data, const int* countOfSpaces);

// рисование границ таблицы (внешних и внутренних)
void dividers(FILE* f, Data* data, const int* countOfSpaces,
    const char* plus, const char* line);

// проверка, что строка - число
int isNumber(char* str);

// рисование границ между столбцами и добаление данных в файл
void drawingLine(FILE* f, Data* data, const int* countOfSpaces);

// итоговая рисовка
void dataFormatting(Data* data, const char* newFileName, const int* countOfSpaces);
