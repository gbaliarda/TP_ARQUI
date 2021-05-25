#include <stdint.h>

typedef struct Time {
	int hour;
	int minutes;
	int seconds;
  int day;
  int month;
  int year;
} Time;

void printf(const char *str);

void putChar(char c);

void printInt(unsigned int num);

int scanf(char *buffer);

int getChar(char *buffer);

int compareStrings(char *str1, char *str2);

void sys_inforeg();

void sys_printmem(uint64_t pointer);

void sys_getDateTime(Time *dateTime);

uint64_t atoi(char *str, int *ok);

uint64_t hex2int(char *hex, int *ok);

void throwInvalidOpcode();

void sys_clearScreen();
