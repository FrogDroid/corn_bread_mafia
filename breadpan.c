#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "sort.h"

//basic error handling from assignment sheet
void printError(){
	char error_message[30] = "An error has occurred\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

int main(int argc, char *argv[])
{
	int max = 512; //the maximum string input length.
  	//start a loop that will run until a user enters "exit"
  	while(i < 3)
	{
		printf("breadpan$> ");
		
	}
}
