#include <keyboard.h>
#include "../include/naiveConsole.h"

#define BUFFER_SIZE 64

static const unsigned char ASCIITable[] = {
     0,   27,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', 0, 8,  
     9, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 0,  '+', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '{', 0, 14,  '}', // 14 es shift izquierdo pressed
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',','.', '-',  15, '*', 0,  ' ', 11, 0, // 15 Shift derecho pressed, 11 bloq mayus
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0xAA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xB6 // 0xAA y 0xB6 shift izquierdo y derecho release
};

// static unsigned char buffer[BUFFER_SIZE];
// static int current = 0;
// static int currentKey = 0;
// int keysToRead = 0;

// // shell -> read() -> retornar en enter
// // si es un alfanumerico, lo imprime. Si es un enter.
// void keyboard_handler() {
//     if (current == BUFFER_SIZE)
//       current = 0;
//     unsigned char key = getKey();
//     // Guardamos solo las letras que tenemos en la tabla, el resto las ignoramos
//     if (key < 58) {
//       buffer[current++] = ASCIITable[key];
//       keysToRead++;
//     }
// }

// char getInput() {
//   if (keysToRead == 0)
//     return 0;
//   if (currentKey == BUFFER_SIZE)
//       currentKey = 0;
//   keysToRead--;
//   return buffer[currentKey++];
// }

static unsigned char actualKey;

void keyboard_handler() {
    unsigned char key = getKey();
    // Guardamos solo las letras que tenemos en la tabla, el resto las ignoramos
    if (key < 183)
      actualKey = ASCIITable[key];
}

// Retorna la key y la destruye
unsigned char getInput() {
  if (!actualKey)
    return 0;
  char aux = actualKey;
  actualKey = 0;
  return aux;
}
