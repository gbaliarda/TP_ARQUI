#include <naiveConsole.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

void scrollDown()
{
	if (((currentVideo - video) / (width*2)) < height - 1)
		return;

	uint16_t * videoChars = video;

	int from = 0, to = width, finish = width * height;
	while (to < finish)
		videoChars[from++] = videoChars[to++];

	while (from < finish)
		videoChars[from++] = 0x0720;

	currentVideo -= width * 2;
}

void ncPrint(const char * string)
{
	int i;
	for (i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}
// Funcion hecha por nosotros 
void ncPrintChar(char character)
{
	scrollDown();
	if (character == '\n')
		ncNewline();
	else {
		*currentVideo = character;
		currentVideo += 2;
	}	
}

void ncNewline()
{
	do
	{
		ncPrintChar(' ');
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void ncPrintDec(uint64_t value)
{
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value)
{
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value)
{
	ncPrintBase(value, 2);
}

// Hace el dump de un registro
void ncPrintReg(const char *regName, uint64_t regValue)
{
	ncPrint(regName);
	ncPrint(": ");
	int digits = uintToBase(regValue, buffer, 16);
	for (int i = 1; i < 16 - digits; i++)
		ncPrint("0");
	ncPrint(buffer);
	ncNewline();
}

void ncPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}

void ncClear()
{
	int i;

	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;
}

int ncBackspace(){
	if(currentVideo >= video + 2){
		*(--currentVideo) = 0x07;
		*(--currentVideo) = 0;
		return 1;
	}
	return 0;
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
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
