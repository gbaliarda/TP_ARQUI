#include "../include/naiveConsole.h"

int64_t write(uint64_t fd, const char* buf, uint64_t count){
    switch (fd) {
      case 1:
        for (int i = 0; i < count; i++)
          ncPrintChar(buf[i]);
        return count;

      default:
        return -1;
    }
}