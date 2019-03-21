#include <string.h>
void assemble(char[]);

int main(int argc, char **argv)
{
	
	
	
	if (argc > 1)
	{
		assemble(argv[1]);
	}
	else
	{
		char filename[128];
		strcpy(filename, "test1.asm");
		assemble(filename);
	}
}
