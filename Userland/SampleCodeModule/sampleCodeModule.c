#include "libc.h"

void executeCommand(char * buffer) {
	int index = 0;
	char command[21];
	char args[5][21]; //Matriz de hasta 5 argumentos con 20 de longitud cada uno

	while (index < 20 && buffer[index] && buffer[index] != ' ') {
		command[index] = buffer[index];
		index++;
	}

	// Comando demasiado largo, no se encuentra
	if (index == 20 && buffer[index] != ' ') {
		printf("Command not found\n");
		return;
	}

	command[index] = 0;
	while (buffer[index] && buffer[index] == ' ') //Si tiene argumentos despues 
		index++; // Salteamos los espacios

	int argNum = 0;	
	while (argNum < 5 && buffer[index]) {
		int indexArg = 0;
		// Leemos argumento
		while (indexArg < 20 && buffer[index] && buffer[index] != ' '){
			args[argNum][indexArg] = buffer[index];
			indexArg++;
			index++;
		}
			
		args[argNum][indexArg] = 0; //0 final del argumento 
		argNum++;

		// Si el argumento era muy largo, se guarda una parte y el resto se descarta
		while (buffer[index] && buffer[index] != ' ')
			index++;
		
		// Avanzo al proximo argumento
		while (buffer[index] && buffer[index] == ' ')
			index++;
			
	}

	if (compareStrings(command, "help")) {
		printf("-------COMMANDS------\n");
		printf("1: help\n");
		printf("2: inforeg\n");
		printf("3: printmem\n");
		printf("4: printDateTime\n");
		printf("5: zeroException\n");
		printf("6: opcodeException\n");
		printf("7: clear\n");
	} 
	else if (compareStrings(command, "inforeg"))
		sys_inforeg();
	else if (compareStrings(command, "printmem")) {
		int ok = 1;
		uint64_t pointer = hex2int(args[0], &ok);
		if(ok)
			sys_printmem(pointer);
		else
			printf("Invalid address\n");
	} else if (compareStrings(command, "printDateTime")) {
		Time dateTime;
		sys_getDateTime(&dateTime);
		printInt(dateTime.day);
		putChar('\\');
		printInt(dateTime.month);
		putChar('\\');
		printInt(dateTime.year);
		putChar(' ');
		printInt(dateTime.hour);
		putChar(':');
		printInt(dateTime.minutes);
		putChar(':');
		printInt(dateTime.seconds);
		putChar('\n');
	} else if (compareStrings(command, "zeroException"))
		printInt(1/0);
	else if (compareStrings(command, "opcodeException"))
		throwInvalidOpcode();
	else if (compareStrings(command, "clear"))
		sys_clearScreen();
	else
		printf("Command not found\n");
	
}

int main() {

	printf("Welcome to the Shell\n\n");

	char buffer[101];
	int charsRead;

	while (1) {
		
		printf("> ");
		charsRead = scanf(buffer);
		executeCommand(buffer);

	}
									
	return 0xDEADBEEF;
}

