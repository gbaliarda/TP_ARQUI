#include <naiveConsole.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
// Cada consola tendra espacio para 39 caracteres (los 2 restantes son un pipe y un espacio que separan ambas)
static uint8_t * currentLeftVideo = (uint8_t*)0xB8000;
static uint8_t * currentRightVideo = (uint8_t*) (0xB8000 + 82);

static char consoleInUse = 0; // 0 = left, 1 = right
static char cursor = 0; // 0 apagado, 1 prendido

void initializeShells(){
	*currentLeftVideo = '>';
	*currentRightVideo = '>';
	currentLeftVideo += 4;
	currentRightVideo += 4;
	currentVideo += 4;
}

void displayCursor() {
	if (!cursor) {
		*currentVideo = '_';
		cursor = 1;
	}
	else 
		deleteCursor();
}

void deleteCursor() {
	*currentVideo = ' ';
	cursor = 0;
}

void changeConsole() {
	if(consoleInUse) {
		currentRightVideo = currentVideo;
		currentVideo = currentLeftVideo;
	} else {
		currentLeftVideo = currentVideo;
		currentVideo = currentRightVideo;
	}
	consoleInUse = !consoleInUse;
}

char getConsoleInUse() {
	return consoleInUse;
}
//Separo la pantalla con | en el medio 
void divideConsoles(){
	uint8_t * auxVideo = video+width-2;
	for(int i = 0; i < height; i++){
		*auxVideo = '|';
		auxVideo += 2;
		*auxVideo = ' ';
		auxVideo += width*2-2;
	}
}

void scrollDown()
{
	if (((currentVideo - video) / (width*2)) < height)
		return;

	uint16_t * videoChars = video;

	int from, to, finish, charsCopied = 0;

	if (consoleInUse) {
		from = width / 2 + 1;
		to = width / 2 + 1 + width;
		finish = width * height;
	}
	else {
		from = 0;
		to = width;
		finish = width * height - (width / 2 + 1);
	}
	while (to < finish) {
		charsCopied++;
		videoChars[from++] = videoChars[to++];
		if (charsCopied % 39 == 0) {
			from += width / 2 + 1;
			to += width / 2 + 1;
		}
	}

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

void ncPrintChar(char character)
{
	scrollDown();
	if (character == '\n')
		ncNewline();
	else {
		*currentVideo = character;
		currentVideo += 2;
	}	

	// Luego de imprimir el ultimo caracter de la derecha, vuelve al inicio de la consola de la derecha
	if(consoleInUse && (currentVideo - video) % (width*2) == 0)  //Caso right
		currentVideo += width+2;
	// Luego de imprimir el ultimo caracter de la izquierda, vuelve al inicio de la consola de la izquierda
	else if(!consoleInUse && (currentVideo - video) % (width*2) == 78) //caso left 
		currentVideo += width+2;
	
}

void ncNewline()
{
	if (consoleInUse) {
		// Imprime espacios hasta que llega al primer caracter de la consola derecha
		do {
			ncPrintChar(' ');
		}
		while((uint64_t)(currentVideo - video) % (width) != 2);
	} 
	else {
		// Imprime espacios hasta que llega al primer caracter de la consola izquierda
		do {
			ncPrintChar(' ');
		}
		while((uint64_t)(currentVideo - video) % (width*2) != 0);
	}
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

void ncClear() {

	uint16_t * videoChars = video;

	int index, finish, charsCopied = 0;

	if (consoleInUse) {
		index = width / 2 + 1;
		finish = width * height;
	}
	else {
		index = 0;
		finish = width * height - (width / 2 + 1);
	}
	while (index < finish) {
		charsCopied++;
		videoChars[index++] = 0x0720;
		if (charsCopied % 39 == 0)
			index += width / 2 + 1;
	}

	if (consoleInUse)
		currentVideo = video + width + 2;
	else
		currentVideo = video;
}

// void lightMode() {

// 	int index, finish, charsCopied = 0;

// 	if (consoleInUse) {
// 		index = width + 2;
// 		finish = width*2 * height;
// 	}
// 	else {
// 		index = 1;
// 		finish = width*2 * height - (width + 2);
// 	}
// 	while (index < finish) {
// 		charsCopied++;
// 		video[index] = 0xf0;
// 		index += 2;
// 		if (charsCopied % 39 == 0)
// 			index += width + 2;
// 	}
// }

int ncBackspace(){
	if(currentVideo >= video + 2){
		deleteCursor();
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
