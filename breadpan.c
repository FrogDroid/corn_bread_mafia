#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>// import wait for prototyping
#include <limits.h>
//basic error handling from assignment sheet
void printError(){
	char error_message[30] = "An error has occurred\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

void breadLs(char *arguments[]);

int main(int argc, char *argv[])
{
	int max = 512; //the maximum string input length.
	char* input = (char*)malloc(max); /* allocate buffer */
    	if (input == 0) exit(1); //There is no more memory to allocate so close the shell.

  	//start a loop that will run until a user enters "exit"
  	while(1) //will run forever unless we tell it to quit.
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
		
		//no we have our input as a string, time to start parsing it out and switching between commands.
		char * command = strtok(input, " ");
		printf("\n command entered: %s \n", command);

		char *arguments[10];
                int a = 1;
                while(a < 10 && arguments[a] != NULL)
                {
                        arguments[a] = strtok( input, " " );
                        a++;
                }

		//we can't use a switch because C is retarded.
		//so here's our if else if bucket code
		if(strcmp (command, "exit") == 0)
		{
			exit(0);
		}
		else if( strcmp ( command, "ls" ) == 0 )
		{
			breadLs(arguments);	
		}
		//todo: enter in the rest of the these commands
		
		else if( strcmp ( command, "wait" ) == 0 ){
		

		}

		 else if( strcmp ( command, "pwd" ) == 0 ){
			char *workDirectory;
			char buff[PATH_MAX + 1];			
			workDirectory= getcwd(buff,PATH_MAX+1);
			printf("%s\n",workDirectory);
                }

		
		else
		{
			printError(); //not a valid command.
		}	
	}
	exit(0); //safe exit at end of while loop.
}

void breadLs(char *arguments[]){
	 int i = 1;
	 int j = 0;
         int child = fork();
         if(child == 0){
	         char *argv[11];//stack allocated array
        	 argv[0] = strdup("/usr/bin/ls");
       		 while(arguments[j] !=NULL){ //the arguments are in an array 1 shorter than the one we are building. i starts at 1 instead of 0
         		argv[i] = arguments[j];
         		i++;
         		j++;
         	}
         	argv[i] = NULL;// terminate command
         	execvp(argv[0],argv);
         	printf("execute failed in LS \n");//test for proper setup
         }

         else if (child > 0){
         	wait(NULL);//wait until complete        
         }

         else {
         	perror("fork");//error
         }

}
