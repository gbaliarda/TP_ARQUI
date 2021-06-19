#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

void ncPrint(const char * string);
void ncPrintChar(char character);
void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncPrintReg(const char *regName, uint64_t regValue);
void ncClear();
int ncBackspace();
void changeConsole();
char getConsoleInUse(); 
void divideConsoles();
void initializeShells();
void displayCursor();
void deleteCursor();

#endif