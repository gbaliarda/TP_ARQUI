typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

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


void printInt(int num) {
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