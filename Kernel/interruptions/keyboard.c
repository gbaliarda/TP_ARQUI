#include <keyboard.h>
#include <interrupts.h>

#define BUFFER_SIZE 64

static const unsigned char ASCIITable[] = {
     0,   0,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', 0xA8, 0,  0,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 0,  '+', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0xA4, '{', 0xB3, 0,  '}',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',','.', '-',  0, '*', 0,  ' '
};

static unsigned char buffer[BUFFER_SIZE];
static int current = 0;
static int currentKey = 0;
int keysToRead = 0;

void keyboard_handler() {
    if (current == BUFFER_SIZE)
      current = 0;
    unsigned char key = getKey();
    // Guardamos solo las letras que tenemos en la tabla, el resto las ignoramos
    if (key < 58) {
      buffer[current++] = ASCIITable[getKey()];
      keysToRead++;
    }
}

char getInput() {
  if (keysToRead == 0)
    return 0;
  if (currentKey == BUFFER_SIZE)
      currentKey = 0;
  keysToRead--;
  return buffer[currentKey++];
}