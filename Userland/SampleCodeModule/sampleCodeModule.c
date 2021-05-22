#include "libc.h"

int main() {

	printf("Welcome to the Shell\n\n");

	char buffer[101];
	int charsRead;

	while (1) {
		
		printf("> ");
		// charsRead = scanf(buffer);
		// printf("\nLeidos con exito los caracteres: ");
		// printf(buffer);
		// putChar('\n');
		// printInt(charsRead);
		// putChar('\n');
		// printf("Ingrese un caracter: ");
		// getChar(buffer);
		// putChar('\n');
		// printf("Char leido: ");
		// printf(buffer);
		// putChar('\n');
		printInt(1 / 0);

	}
									
	return 0xDEADBEEF;

	// while (1)
	// {
	// 	scanf();		// kernel espera con _hlt hasta un enter
	// 	parseCommand();
	// 	executeCommand();
	// }
}