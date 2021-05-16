#include <stdint.h>
#include "../include/naiveConsole.h"
#include "syscalls.h"

static int sysNum;

void loadSysNum(int64_t rax)
{
  sysNum = rax;
}

int64_t syscallDispatcher(int64_t arg0, int64_t arg1, int64_t arg2)
{
    switch (sysNum) {
      case 1:
          return write((uint64_t) arg0, (const char*) arg1, (uint64_t) arg2);
      
      default:
        return -1; 
    }
}
