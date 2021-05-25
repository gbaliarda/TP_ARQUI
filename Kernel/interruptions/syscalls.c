#include "../include/naiveConsole.h"
#include "keyboard.h"
#include "interrupts.h"
#include "syscalls.h"

int mayus = 0;

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
		unsigned char key = getInput();
		if (key == 0)
      continue;
    if (key == '\n') {
      ncNewline();
      buf[count] = 0; // Termina en 0
      return count;
    }
    // Backspace
    else if (key == 8) {
      if (count > 0 && ncBackspace())
        count--;
    }
    // Bloq Mayus
    else if (key == 11) {
      mayus = !mayus;
    }
    else if (key == 14 || key == 15) {
      mayus = 1;
    }
    else if (key == 0xAA || key == 0xB6) {
      mayus = 0;
    }
    else {
      if(mayus && key >= 'a' && key <= 'z')
        key -= 'a' - 'A';
      
      // Solo guardamos hasta 100 caracteres en el comando, el resto se imprimiran solamente
      if (count < 100)
        buf[count] = key;
      count++;
      ncPrintChar(key);
    }
	}
  buf[count] = 0; // Termina en 0
  return (count >= 100) ? 100 : count; // Como solo se guardan hasta 100 caracteres en el buffer, se retornan hasta 100
}

void inforeg() {
  dumpRegs();
}

void printmem(uint64_t pointer) {
  uint8_t *arr = (uint8_t*) pointer;
  for (int i = 0; i < 32; i++){
    ncPrintHex(arr[i]);
    ncPrint(" ");
  }
  ncNewline();
}

void getDateTime(Time *dayTime) {
  getTimeRTC(dayTime);
}

void clearScreen(){
  ncClear();
}