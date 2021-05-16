void sys_write(unsigned int fd, const char *buffer, unsigned int count);
int sys_read(char *buffer);

int main() {

	sys_write(1, "Welcome to the Shell\n", 21);
	sys_write(1, "Chau\n", 5);

	char buffer[100];
	int charsRead;

	while (1) {
		
		charsRead = sys_read(buffer);
		sys_write(1, "\nLeidos con exito los caracteres\n", 32);

	}
	
	return 0xDEADBEEF;

	// while (1)
	// {
	// 	scanf();		// kernel espera con _hlt hasta un enter
	// 	parseCommand();
	// 	executeCommand();
	// }
}