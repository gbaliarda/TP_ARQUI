#include "libc.h"
#define ULONG_MAX 18446744073709551615

void sys_write(unsigned int fd, const char *buffer, unsigned int count);
int sys_read(char *buffer, int limit);

static int strlen(const char *str) {
  int len = 0;
  while (str[len] != 0)
    len++;
  return len;
}

void printf(const char *str) {
  sys_write(1, str, strlen(str));
}

void putChar(char c) {
  sys_write(1, &c, 1);
}

int scanf(char *buffer) {
  return sys_read(buffer, -1);
}

int getChar(char *buffer) {
  return sys_read(buffer, 1);
}

// Int con signo to string 
void itos(int value, char* target){
    int digit; 
    int sign = 1; // 0 negativo, 1 positivo
    int i = -1, j = 0;
    char aux[11];
    if(value < 0){
        sign = 0;
        value *= -1;
    }
    do{
        i++;
        digit = value % 10;
        aux[i] = digit + '0'; // 48 = '0' 
        value /= 10; 
    } while(value > 0);
    if (!sign){ //Si es negativo le agrego el - al principio
        target[j++] = '-';
    } 
    while(i > -1){ //Doy vuelta al aux y lo guardo en target
        target[j++] = aux[i--];
    }
    target[j] = 0;
}

static uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

void printInt(unsigned int num) {
  char buffer[10];
  int digits = uintToBase(num, buffer, 10);
  sys_write(1, buffer, digits);
}

int compareStrings(char *str1, char *str2){
  int index = 0;
  
  while(str1[index] && str2[index]){
    if(str1[index] != str2[index])
      return 0;
    index++;
  }
  
  if(str1[index] || str2[index]) //Si no tiene la misma long
    return 0;
  return 1;
}

/**
 * hex2int
 * take a hex string and convert it to a 32bit number (max 8 hex digits)
 */
uint64_t hex2int(char *hex, int *ok) {
    uint64_t val = 0;
    while (*hex) {
        // Checkeamos si se pasa de una direccion de memoria de 64 bits
        if(val > ULONG_MAX / 10) {
          *ok = 0;
          return 0;
        }
        // get current character then increment
        uint8_t byte = *hex++;
        
        if (!(byte >= '0' && byte <= '9') && !(byte >= 'a' && byte <= 'f') && !(byte >= 'A' && byte <= 'F')) {
          *ok = 0;
          return 0;
        }
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
        // shift 4 to make space for new digit, and add the 4 bits of the new digit 
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}


//[0, +18,446,744,073,709,551,615]
uint64_t atoi(char *str, int *ok){
  uint64_t num = 0;
  
  for (int i = 0; str[i]; ++i) {
    if(str[i] < '0' || str[i] > '9') {
      *ok = 0;
      return 0;
    }
    else {
      if(num > ULONG_MAX / 10) {
        *ok = 0;
        return 0;
      }
      num = num * 10 + str[i] - '0';
    }
  }

  return num;
}
