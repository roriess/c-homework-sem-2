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

void dividers(FILE* f, Data* data, const int* countOfSpaces,
    const char* left, const char* middle, const char* right, const char* line)
{
    fprintf(f, left);
    fprintf(f, line);
    for (int i = 0; i < data->columnCount; i++) {
        for (int j = 0; j < countOfSpaces[i]; j++)
            fprintf(f, line);
        if (i + 1 != data->columnCount) {
            fprintf(f, line);
            fprintf(f, middle);
            fprintf(f, line);
        }
    }
    fprintf(f, line);
    fprintf(f, right);
    fprintf(f, "\n");
}

int isDigit(char* str)
{
    char* elements[11] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "." };
    int flag = 0;
    for (int i = 0; i < 11; i++) {
        if (str == elements[i])
            flag = 1;
    }
    return flag;
}

int isNumber(char* str[])
{
    for (int i = 0; str[i] != "\0"; i++) {
        if (!isDigit(str[i]))
            return 0;
    }
    return 1;
}

void drawindLine(FILE* f, Data* data, const int* countOfSpaces,
    char* titleDivider, char* ordinaryDivider)
{
    int flag = 1; // flag == 1 - заголовок
    for (int i = 0; i < data->linesCount; i++) {
        const char* str = data->data[i];
        fprintf(f, titleDivider);
        fprintf(f, " ");
        int countWidth = 0, columnNumber = 0;
        for (int j = 0; str[j] != '\0'; j++) {
            char* buffer = malloc(sizeof(char*) * countOfSpaces[columnNumber]);
            int len = 0;
            if (str[j] != ',') {
                buffer[len++] = str[j];
                fprintf(f, "%c", str[j]);
                countWidth++;
            } else {
                if (countWidth < countOfSpaces[columnNumber]) {
                    for (int k = 0; k < countOfSpaces[columnNumber] - countWidth; k++)
                        fprintf(f, " ");
                }
                fprintf(f, " ");
                if (flag) {
                    fprintf(f, "%s", titleDivider);
                } else {
                    fprintf(f, "%s", ordinaryDivider);
                }
                fprintf(f, " ");
                columnNumber++;
                free(buffer);
                char* buffer = malloc(sizeof(char*) * countOfSpaces[columnNumber]);
                len = 0, countWidth = 0;
            }
        }
        if (countWidth < countOfSpaces[columnNumber]) {
            for (int k = 0; k < countOfSpaces[columnNumber] - countWidth; k++)
                fprintf(f, " ");
        }
        fprintf(f, " ");
        fprintf(f, titleDivider);
        fprintf(f, "\n");

        if (i + 1 < data->linesCount) {
            if (!flag) {
                dividers(f, data, countOfSpaces, "+", "+", "+", "⁠-");
            } else {
                dividers(f, data, countOfSpaces, "+", "+", "+", "=");
                flag = 0;
            }
        }
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
    dividers(f, data, countOfSpaces, "+", "+", "+", "=");
    drawindLine(f, data, countOfSpaces, "|", "|");
    dividers(f, data, countOfSpaces, "+", "+", "+", "=");
    fclose(f);
}
