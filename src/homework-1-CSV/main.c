#include "operations.h"
#include <stdio.h>
#include <string.h>

void testAll();

int main(int argc, char* argv[])
{
    if (argc < 3)
        return 1;
    const char* inputName = argv[1];
    const char* outputName = argv[2];

    if (argc == 4 && strcmp(argv[3], "--test") == 0)
        testAll();

    Data* text = readText(inputName);
    dataFormatting(text, outputName, columnWidth(text));

    return 0;
}
