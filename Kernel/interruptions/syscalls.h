#ifndef SYSCALLS_H_
#define SYSCALLS_H_

void syscallHandler();

int64_t write(uint64_t fd, const char* buf, uint64_t count);

#endif