#include "operations.c"
#include <stdio.h>

void main()
{
    Data* text = readText("input.csv");
    text->columnCount = countColumns(text);
    dataFormatting(text, "output.txt", columnWidth(text));
}
