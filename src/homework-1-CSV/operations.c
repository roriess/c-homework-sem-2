#include "operations.h"
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

    while (!feof(f)) {
        char* buffer = malloc(sizeof(char) * 100);
        if (buffer == NULL)
            return NULL;
        const int readBytes = fscanf(f, "%[^\n]", buffer);
        if (readBytes < 0) {
            free(buffer);
            break;
        }

        if (data->linesCount >= maxLines) {
            maxLines *= 2;
            const char** temp = realloc(data->data, sizeof(char*) * maxLines);
            if (temp == NULL) {
                printf("Memory allocation error.\n");
                free(buffer);
                break;
            }
            data->data = temp;
        }

        data->data[data->linesCount] = buffer;
        data->linesCount++;

        // так как scanf читает до '\n', удалаяем оставшийся символ '\n'
        int c = fgetc(f);
        if (c != EOF && c != '\n')
            ungetc(c, f);
    }
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
    fprintf(f, plus);
    fprintf(f, line);
    for (int i = 0; i < data->columnCount; i++) {
        for (int j = 0; j < countOfSpaces[i]; j++)
            fprintf(f, line);
        if (i + 1 != data->columnCount) {
            fprintf(f, line);
            fprintf(f, plus);
            fprintf(f, line);
        }
    }
    fprintf(f, line);
    fprintf(f, plus);
    fprintf(f, "\n");
}

int isNumber(char* str[])
{
    char* elements[11] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "." };
    for (int i = 0; str[i] != "\0"; i++) {
        int flag = 0;
        for (int j = 0; j < 11; j++) {
            if (str[i] == elements[i])
                flag = 1;
        }
        if (!flag)
            return 0;
    }
    return 1;
}

void drawingLine(FILE* f, Data* data, const int* countOfSpaces, char* divider)
{
    char* buffer;
    int widthOfTable = tableWidth(data, countOfSpaces);
    for (int i = 0; i < data->linesCount; i++) {
        const char* str = data->data[i];
        int columnNumber = 0;
        buffer = malloc(sizeof(char) * widthOfTable);
        int lenBuffer = 0;
        for (int j = 0; str[j] != '\0'; j++) {
            if (str[j] != ',') {
                buffer[lenBuffer++] = str[j];
            } else {
                buffer[lenBuffer] = '\0';
                fprintf(f, "│ %-*s ", countOfSpaces[columnNumber], buffer);
                columnNumber++;
                free(buffer);
                buffer = malloc(sizeof(char) * widthOfTable);
                lenBuffer = 0;
            }
        }
        buffer[lenBuffer] = '\0';
        fprintf(f, "│ %-*s |", countOfSpaces[columnNumber], buffer);
        fprintf(f, "\n");
        free(buffer);

        if (i + 1 < data->linesCount)
            dividers(f, data, countOfSpaces, "+", "-");
    }
}

void dataFormatting(Data* data, const char* newFileName, const int* countOfSpaces)
{
    FILE* f = fopen(newFileName, "w");
    if (f == NULL) {
        printf("File not found or created.");
        exit(1);
    }
    const int widthOfTable = tableWidth(data, countOfSpaces);
    dividers(f, data, countOfSpaces, "+", "=");
    drawingLine(f, data, countOfSpaces, "|");
    dividers(f, data, countOfSpaces, "+", "=");
    fclose(f);
}
