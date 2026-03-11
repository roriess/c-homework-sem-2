#include "operations.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXLINELENGTH 100

int main(int argc, char* argv[])
{
    if (argc < 2)
        return 1;

    if (argc == 3 && strcmp(argv[2], "--test") == 0) {
        test();
    } else {
        int airportCount = loadAirports();
        printf("Загружено %d аэропортов. Система готова к работе.\n", airportCount);

        char line[MAXLINELENGTH];
        while (1) {
            fgets(line, MAXLINELENGTH, stdin);

            char command[20];
            char argument[100];
            sscanf(line, "%s %99[^\n]", command, argument);

            if (strcmp(command, "find") == 0)
                findAirport(argument);

            if (strcmp(command, "add") == 0)
                addAirport(argument);

            if (strcmp(command, "delete") == 0)
                deleteAirport(argument);

            if (strcmp(command, "save") == 0)
                saveCurrentStatus();

            if (strcmp(command, "quit") == 0)
                quit();
        }
        return 0;
    }
}
