/*
*  Zos Attempt 5 v0.5
*  Author: Zac McChesney
*/
#include <system.h>

int acceptInput = 0;
char inputText[128] = "\0";
int inputCount = 0;

void shell()
{
	keyboard_install();
	puts("User>");
	acceptInput = 1;
	
	puts("You entered ");
	puts(inputText);
	puts("\n");
}

int commandExists(char* command)
{
	if (command == "help")
	{
		
	}
	if (command != "help" || command != "zfs")
	{
		
	}
}
