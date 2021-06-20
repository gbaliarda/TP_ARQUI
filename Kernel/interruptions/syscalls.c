#include "../include/naiveConsole.h"
#include "keyboard.h"
#include "interrupts.h"
#include "syscalls.h"
#include "time.h"

int mayus = 0;
int countLeft = 0, countRight = 0;

Registers b, bAux;
Registers *backupRegisters = &b;
Registers *backupAuxRegisters = &bAux;

void loadRegisters(Registers* registers, Registers *from);

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

int read(char* buf, int limit, int *changed) 
{
  char console = getConsoleInUse(); // 0 = left, 1 = right
  int count = console ? countRight : countLeft;

  while (1 && (count < limit || limit == -1))
  {
		_hlt();
    if (ticks_elapsed() % 9 == 0)
      displayCursor();
		unsigned char key = getInput();

    switch (key) {
      case 0:
        continue;
        break;

      case '\n':
        ncNewline();
        if (console) 
          countRight = 0;
        else
          countLeft = 0;
        buf[count] = 0; // Termina en 0
        return count;

      case 8:
        if (count > 0 && ncBackspace())
          count--;
        break;

      case 9:
        *changed = 1;
        if (console)
          countRight = count;
        else
          countLeft = count;
        deleteCursor();
        changeConsole();
        return count;

      // F1, guarda el estado de los registros en el momento actual
      case 17:
        loadRegisters(backupRegisters, backupAuxRegisters);
        break;

      // shifts izq, der y sus release; y bloq mayus
      case 11:
      case 14:
      case 15:
      case 0xAA:
      case 0xB6:
        mayus = !mayus;
        break;
      
      default: 
        if(mayus && key >= 'a' && key <= 'z')
        key -= 'a' - 'A';
        // Solo guardamos hasta 100 caracteres en el comando, el resto se imprimiran solamente
        if (count < 100)
          buf[count] = key;
        count++;
        ncPrintChar(key);
        break;
    }
	}
  buf[count] = 0; // Termina en 0
  return (count >= 100) ? 100 : count; // Como solo se guardan hasta 100 caracteres en el buffer, se retornan hasta 100
}

void loadRegisters(Registers* registers, Registers *from) {
  registers->rax = from->rax;
	registers->rbx = from->rbx;
	registers->rcx = from->rcx;
	registers->rdx = from->rdx;
	registers->rbp = from->rbp;
	registers->rdi = from->rdi;
	registers->rsi = from->rsi;
	registers->r8 = from->r8;
	registers->r9 = from->r9;
	registers->r10 = from->r10;
	registers->r11 = from->r11;
	registers->r12 = from->r12;
	registers->r13 = from->r13;
	registers->r14 = from->r14;
	registers->r15 = from->r15;
}

// Devuelve el ultimo estado guardado de los registros
void inforeg(Registers *registers) {
  loadRegisters(registers, backupRegisters);
}

// Guarda un backup auxiliar, por si la tecla es F1 y necesitamos quedarnoslo
void saveBackup() {
  saveState(backupAuxRegisters);
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

char consoleInUse() {
  return getConsoleInUse();
}