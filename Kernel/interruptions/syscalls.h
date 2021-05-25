#ifndef SYSCALLS_H_
#define SYSCALLS_H_

typedef struct Time {
	int hour;
	int minutes;
	int seconds;
  int day;
  int month;
  int year;
} Time;

void syscallHandler();

int64_t write(uint64_t fd, const char* buf, uint64_t count);

int read(char *buf, int limit);

void inforeg();

void printmem(uint64_t pointer);

void getDateTime(Time *dayTime);

void clearScreen();

#endif