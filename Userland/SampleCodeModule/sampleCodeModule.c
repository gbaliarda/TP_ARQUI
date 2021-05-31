#include "libc.h"

typedef struct buffersStruct {
  char bufferLeft[101];
  char bufferRight[101];
} buffersStruct;

typedef buffersStruct *Buffers;

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
		printf("8: computeZeros\n");
		printf("9: cpuid\n");
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
	} 
	else if (compareStrings(command, "printDateTime")) {
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
	} 
	else if (compareStrings(command, "zeroException"))
		printInt(1/0);
	else if (compareStrings(command, "opcodeException"))
		throwInvalidOpcode();
	else if (compareStrings(command, "clear"))
		sys_clearScreen();
	else if (compareStrings(command, "computeZeros")) {
		char res[11];
		int ok = 1;
		double a, b, c;
		a = strToDouble(args[0], &ok);
		b = strToDouble(args[1], &ok);
		c = strToDouble(args[2], &ok);
		if (!ok) {
			printf("Invalid arguments a, b or c\n");
			return;
		}
		double root1;
		double root2;
		if (computeZeros(a, b, c, &root1, &root2)) {
			dtos(root1, res);
			printf("Root 1: ");
			printf(res);
			putChar('\n');
			dtos(root2, res);
			printf("Root 2: ");
			printf(res);
			putChar('\n');
		} 	
		else
			printf("Roots are not real numbers\n");
	}
	else if (compareStrings(command, "cpuid")) {
		cpuInformation cpuidData;
		cpuid(&cpuidData);

		printf("sse: ");
		cpuidData.sse ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');

		printf("sse2: ");
		cpuidData.sse2 ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');

		printf("sse3: ");
		cpuidData.sse3 ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');

		printf("pclmulqdq: ");
		cpuidData.pclmulqdq ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');

		printf("fma: ");
		cpuidData.fma ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');

		printf("sse4.1: ");
		cpuidData.sse41 ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');

		printf("sse4.2: ");
		cpuidData.sse42 ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');

		printf("avx: ");
		cpuidData.avx ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');

		printf("f16c: ");
		cpuidData.f16c ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');

		printf("vpclmulqdq: ");
		cpuidData.vpclmulqdq ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');

		printf("avx2: ");
		cpuidData.avx2 ? printf("ACTIVADO") : printf("DESACTIVADO");
		putChar('\n');
	} 
	else
		printf("Command not found, try 'help'\n");
	
}

int main() {
	
	Buffers buffers; //Puntero de tipo buffersStruct 

	char *buffer;
	buffer = buffers->bufferLeft;
	int charsRead;
	int changed = 1;

	while (1) {
		
		if (!changed)
			printf("> ");
		else
			changed = 0;
		charsRead = scanf(buffer, &changed);

		if (changed) {
			if (buffer == buffers->bufferLeft)
				buffer = buffers->bufferRight;
			else
				buffer = buffers->bufferLeft;
			continue;
		}
		executeCommand(buffer);

	}
									
	return 0xDEADBEEF;
}

