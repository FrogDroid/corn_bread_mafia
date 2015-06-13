#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

//basic error handling from assignment sheet
void printError(){
	char error_message[30] = "An error has occurred\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

int main(int argc, char *argv[])
{
	int max = 512; //the maximum string input length.
	char* input = (char*)malloc(max); /* allocate buffer */
    	if (input == 0) exit(1); //There is no more memory to allocate so close the shell.

	int w = 0; //just for a test currently.
  	//start a loop that will run until a user enters "exit"
  	while(w < 3) // I don't want to be running an infinite loop yet.
	{
		printf("breadpan$> "); //shell prompt

		/**
		* See see http://stackoverflow.com/questions/7831755/what-is-the-simplest-way-of-getting-user-input-in-c/
		* for a discussion on the best practices for reading input. They show how to handle dynamic memory allocation which we will be implementing for 
		* correctness.
		*/

		while (1) 
		{ /* skip leading whitespace */
     			int c = getchar();
        		if (c == EOF) break; /* end of file */
        		if (!isspace(c)) {
             			ungetc(c, stdin);
             			break;
        		}
    		}

		int i = 0;
    		while (1) 
		{
        		int c = getchar();
        		if (isspace(c) || c == EOF) { /* at end, add terminating zero */
            			input[i] = 0;
            			break;
        		}
        		input[i] = c;
        		if (i == max - 1) { /* buffer full */
            			max = max + max;
            			input = (char*)realloc(input, max); /* get a new and larger buffer */
            			if (input == 0) exit(1); //out of memory
        		}
        		i++;
    		}
		
		w++; //Testing purposes.
	}
	exit(0); //safe exit at end of while loop.
}
