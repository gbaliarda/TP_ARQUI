#include "libc.h"

void executeCommand(char * buffer){
	int index = 0;
	char command[21];
	while(index < 20 && buffer[index] && buffer[index] != ' '){
		command[index] = buffer[index];
		index++;
	}
	command[index] = 0;
	if(compareStrings(command, "inforeg")){
		sys_inforeg();
	} else if(compareStrings(command, "help")){
		printf("-------COMMANDS------\n");
		printf("1: help\n");
		printf("2: inforeg\n");
	}
	
}

int main() {

	printf("Welcome to the Shell\n\n");

	char buffer[101];
	int charsRead;

	while (1) {
		
		//printInt(1 / 0);
		
		printf("> ");
		charsRead = scanf(buffer);
		executeCommand(buffer);
		

	}
									
	return 0xDEADBEEF;

	// while (1)
	// {
	// 	scanf();		// kernel espera con _hlt hasta un enter
	// 	parseCommand();
	// 	executeCommand();
	// }
}

