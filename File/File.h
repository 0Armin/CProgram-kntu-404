#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Cell-Sheet/sheet.h"

#define MAX_LINE 1024

typedef enum {
    FILE_OK = 0,
    FILE_CANT_OPEN,
    FILE_CANT_READ,
    FILE_CANT_WRITE,
    FILE_BAD_FORMAT
} FileError;

/* Core I/O */
FileError loadSheetFromFile(Sheet* sheet, const char* filename);
FileError saveSheetToFile(const Sheet* sheet, const char* filename);

/* Utilities used across File module */
char* trimSpace(char* str);
int countCSVColumns(const char *line);
int parseValue(const char* token, Sheet* sheet, int row, int col);
void makeAddress(int row, int col, char* buffer, size_t size);
int checkAddress(const char* address);
int addressToIndex(const char* address, int* row, int* col);
char* readWholeFile(const char* filename);

/* Format checks */
int isValidLine(const char *line);
int isValidFile(const char* filename);
int detectFileFormat(const char* filename);
int validateCSVFile(const char *filename);

#endif
