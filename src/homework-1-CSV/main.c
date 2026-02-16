#include "operations.c"
#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
        return 1;

    const char* inputName = argv[1];
    const char* outputName = argv[2];

    Data* text = readText(inputName);
    text->columnCount = countColumns(text);
    dataFormatting(text, outputName, columnWidth(text));
}
