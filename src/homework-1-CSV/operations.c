#include "operations.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

Data* readText(const char* fileName)
{
    FILE* f = fopen(fileName, "r");
    if (f == NULL) {
        printf("File not found.");
        return NULL;
    }

    int maxLines = 100;
    Data* data = malloc(sizeof(Data));
    if (data == NULL)
        return NULL;
    data->data = malloc(sizeof(char*) * maxLines); // массив указателей на строки файла
    if (data->data == NULL) {
        free(data);
        return NULL;
    }
    data->linesCount = 0;

    char* buffer = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&buffer, &len, f)) != -1) {
        if (read > 0 && buffer[read - 1] == '\n')
            buffer[read - 1] = '\0';

        if (data->linesCount >= maxLines) {
            maxLines *= 2;
            char** temp = realloc(data->data, sizeof(char*) * maxLines);
            if (temp == NULL) {
                printf("Memory allocation error.\n");
                free(buffer);
                break;
            }
            data->data = temp;
        }

        data->data[data->linesCount] = buffer;
        data->linesCount++;

        buffer = NULL;
        len = 0;
    }
    if (buffer)
        free(buffer);
    fclose(f);
    return data;
}

const int countColumns(Data* data)
{
    const char* str = data->data[0];
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',')
            count++;
    }
    return count + 1;
}

const int* columnWidth(Data* data)
{
    int columnCount = countColumns(data);
    int* spaces = malloc(sizeof(int) * columnCount);
    for (int i = 0; i < columnCount; i++)
        spaces[i] = 0;

    for (int i = 0; i < data->linesCount; i++) {
        const char* str = data->data[i];
        int count = 0;
        int columnNumber = 0;
        for (int j = 0; str[j] != '\0'; j++) {
            if (str[j] != ',') {
                count++;
            } else {
                if (count > spaces[columnNumber])
                    spaces[columnNumber] = count;
                columnNumber++;
                count = 0;
            }
        }
        if (count > spaces[columnNumber])
            spaces[columnNumber] = count;
    }
    return spaces;
}

const int tableWidth(Data* data, const int* countOfSpaces)
{
    int widthOfTable = 0;
    for (int i = 0; i < data->columnCount; i++)
        widthOfTable += countOfSpaces[i];
    return widthOfTable;
}

void dividers(FILE* f, Data* data, const int* countOfSpaces, const char* plus, const char* line)
{
    fputs(plus, f);
    fputs(line, f);
    for (int i = 0; i < data->columnCount; i++) {
        for (int j = 0; j < countOfSpaces[i]; j++)
            fputs(line, f);
        if (i + 1 != data->columnCount) {
            fputs(line, f);
            fputs(plus, f);
            fputs(line, f);
        }
    }
    fputs(line, f);
    fputs(plus, f);
    fputs("\n", f);
}

int isNumber(char* str)
{
    int countDots = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            if (str[i] == '.') {
                countDots++;
                if (countDots > 1)
                    return 0;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

void drawingLine(FILE* f, Data* data, const int* countOfSpaces, char* divider)
{
    dividers(f, data, countOfSpaces, "+", "=");
    int widthOfTable = tableWidth(data, countOfSpaces);
    char* buffer = malloc(sizeof(char) * (widthOfTable + 1));

    for (int i = 0; i < data->linesCount; i++) {
        const char* str = data->data[i];
        int columnNumber = 0;
        int lenBuffer = 0;
        for (int j = 0; str[j] != '\0'; j++) {
            if (str[j] != ',') {
                buffer[lenBuffer++] = str[j];
            } else {
                buffer[lenBuffer] = '\0';
                int isNum = isNumber(buffer);
                if (isNum) {
                    fprintf(f, "│ %*s ", countOfSpaces[columnNumber], buffer);
                } else {
                    fprintf(f, "│ %-*s ", countOfSpaces[columnNumber], buffer);
                }

                lenBuffer = 0;
                columnNumber++;
            }
        }

        buffer[lenBuffer] = '\0';
        int isNum = isNumber(buffer);
        if (isNum) {
            fprintf(f, "│ %*s |", countOfSpaces[columnNumber], buffer);
        } else {
            fprintf(f, "│ %-*s |", countOfSpaces[columnNumber], buffer);
        }
        fputs("\n", f);

        if (i + 1 < data->linesCount) {
            if (i == 0) {
                dividers(f, data, countOfSpaces, "+", "=");
            } else {
                dividers(f, data, countOfSpaces, "+", "-");
            }
        }
    }
    dividers(f, data, countOfSpaces, "+", "-");
    free(buffer);
}

void dataFormatting(Data* data, const char* newFileName, const int* countOfSpaces)
{
    FILE* f = fopen(newFileName, "w");
    if (f == NULL) {
        printf("File not found or created.");
        exit(1);
    }
    const int widthOfTable = tableWidth(data, countOfSpaces);
    drawingLine(f, data, countOfSpaces, "|");
    fclose(f);
}
