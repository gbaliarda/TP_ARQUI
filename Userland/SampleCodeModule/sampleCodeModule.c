/* sampleCodeModule.c */

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

void sys_write(unsigned int fd, const char *buffer, unsigned int count);
int getColor();


int main() {
	//All the following code may be removed 
	*v = 'X';
	int color = getColor();
	*(v+1) = color;
	// *(v+1) = 0x74;

	sys_write(1, "Hello World", 10);

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;

	// while (1)
	// {
	// 	scanf();		// kernel espera con _hlt hasta un enter
	// 	parseCommand();
	// 	executeCommand();
	// }
}