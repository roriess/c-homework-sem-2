#include "operations.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELENGTH 100

int main(int argc, char* argv[])
{
    if (argc < 2)
        return 1;

    // int airportCount = loadAirports();
    // printf("Загружено %d аэропортов. Система готова к работе.\n", airportCount);

    // char line[MAXLINELENGTH];
    // while (1)
    // {
    //     fgets(line, MAXLINELENGTH, stdin);

    //     char command[20];
    //     char argument[100];
    //     sscanf(line, "%s %[^\n]", command, argument);

    //     if (command == "find") {
    //         findAirport(argument);
    //     }
    //     if (command == "add") {
    //         addAirport(argument);
    //     }
    //     if (command == "delete") {
    //         deleteAirport(argument);
    //     }
    //     if (command == "save") {
    //         saveСurrentStatus();
    //     }
    //     if (command == "quit")
    //         return;
    // }
}
