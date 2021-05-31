#include <stdint.h>

typedef struct Time {
	int hour;
	int minutes;
	int seconds;
  int day;
  int month;
  int year;
} Time;

void sys_write(unsigned int fd, const char *buffer, unsigned int count);

int sys_read(char *buffer, int limit, int *changed);

void printf(const char *str);

void putChar(char c);

void printInt(unsigned int num);

int scanf(char *buffer, int *changed);

int getChar(char *buffer, int *changed);

int compareStrings(char *str1, char *str2);

void sys_inforeg();

void sys_printmem(uint64_t pointer);

void sys_getDateTime(Time *dateTime);

uint64_t atoi(char *str, int *ok);

uint64_t hex2int(char *hex, int *ok);

void throwInvalidOpcode();

void sys_clearScreen();

// Retorna 0 si las raices son imaginarias, 1 si son reales
int computeZeros(double a, double b, double c, double *root1, double *root2);

void dtos(double num, char *buff);

double strToDouble(char *str, int *ok);
