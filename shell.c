/*
*  Zos Attempt 5 v0.5
*  Author: Zac McChesney
*/
#include <system.h>

int acceptInput = 0;
char inputText[1024] = "\0";
int inputCount = 0;

void shell()
{
	exitLoop = 0;
	puts("User>");
	acceptInput = 1;
}

