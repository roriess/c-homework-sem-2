#include "operations.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_KEY_LENGTH 10
#define MAX_NAME_LENGTH 90

int main(int argc, char* argv[])
{
    if (argc < 2) return 1;

    if (argc == 3 && strcmp(argv[2], "--test") == 0) {
        AVLTree* tree = createAVLTree();
        if (tree == NULL) return -1;
        testTree();
    } else {
        AVLTree* tree = loadAirports(NULL);
        unsigned int airportCount = getAirportCount(tree);
        printf("Загружено %d аэропортов. Система готова к работе.\n", airportCount);

        char line[MAX_LINE_LENGTH];
        while (1) {
            fgets(line, MAX_LINE_LENGTH, stdin);

            char command[20];
            char argument[100];
            sscanf(line, "%s %99[^\n]", command, argument);

            if (strcmp(command, "find") == 0) {
                char* airportName = findAirport(tree, argument);
                if (airportName) {
                    printf("%s → %s\n", argument, airportName);
                } else {
                    printf("Аэропорт с кодом '%s' не найден в базе.\n", argument);
                }
            }

            if (strcmp(command, "add") == 0) {
                char key[MAX_KEY_LENGTH];
                char name[MAX_NAME_LENGTH];
                if (sscanf(argument, "%[^:]:%[^\n]", key, name) == 2) {
                    if (addAirport(tree, key, name) == 0) {
                        printf("Аэропорт '%s' добавлен в базу.\n", key);
                    } else {
                        printf("Аэропорт с кодом '%s' уже существует.\n", key);
                    }
                }
            }

            if (strcmp(command, "delete") == 0) {
                if (deleteAirport(tree, argument) == 0) {
                    printf("Аэропорт '%s' удалён из базы.\n", argument);
                } else {
                    printf("Аэропорт с кодом '%s' не найден в базе.\n", argument);
                }
            }

            if (strcmp(command, "save") == 0) {
                unsigned int airportCount = saveCurrentStatus(tree);
                printf("База сохранена: %u аэропортов.\n", airportCount);
            }

            if (strcmp(command, "quit") == 0) {
                quit(tree);
                break;
            }
        }
        return 0;
    }
}
