#include "../include/naiveConsole.h"
#include "keyboard.h"
#include "interrupts.h"

int64_t write(uint64_t fd, const char* buf, uint64_t count) {
  switch (fd) {
    case 1:
      for (int i = 0; i < count; i++)
        ncPrintChar(buf[i]);
      return count;

    default:
      return -1;
  }
}

int read(char* buf, int limit) 
{
  int count = 0;
  while (1 && (count < limit || limit == -1))
  {
		_hlt();
		char key = getInput();
		if (key > 0) {
      if (key == '\n'){
        ncNewline();
        buf[count] = 0; // Termina en 0
        return count;
      }
      // Backspace
      else if (key == 8) {
        if (ncBackspace())
          count--;
      }
      else {
        // Solo guardamos hasta 100 caracteres en el comando, el resto se imprimiran solamente
        if (count < 100)
          buf[count] = key;
        count++;
        ncPrintChar(key);
      }
    }
	}
  buf[count] = 0; // Termina en 0
  return count;
}

void inforeg() {
  dumpRegs();
}
