#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>// import wait for prototyping
#include <limits.h>

//sorry about all the bad bread puns.
#define BREAD_PAN 512
#define BREAD_SLICE 16
#define BREAD_SLICE_TOK " "
//basic error handling from assignment sheet
void printError(){
	char error_message[30] = "An error has occurred\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

void breadLs(char **args);
char **slice(char *in);
char *bread_read();
int  toast(char **args);

int main(int argc, char *argv[])
{
	char* input; /* allocate buffer */
	int status = 0;

  	//start a loop that will run until a user enters "exit"
  	do //will run forever unless we tell it to quit.
	{
		printf("breadpan$> "); //shell prompt

		//no we have our input as a string, time to start parsing it out and switching between commands.
		//printf("\n command entered: %s \n", command);
		input = bread_read();

		//so here's our if else if bucket code
printf("parsing args \n");
		char **args= slice(input);//create out array of strings to inpuit args...hoping this will work
printf("args parsed \n");
		toast(args);
		//let's free up those buffers.
		free(input);
		free(args);
	}while(status);
	exit(0); //safe exit at end of while loop.
}

void breadLs(char **arguments){ //changed this to accept array of strings
	 int status;
         int child = fork();
         if(child == 0){
		printf("ls called \n");
		//child
       	//	arguments[0] = strdup("/bin/ls");
         	if(execvp(arguments[0], arguments)  == -1) printError();
         }
         else if (child > 0){
        	 do {
     			 waitpid(child, &status, WUNTRACED);
    		} while (!WIFEXITED(status) && !WIFSIGNALED(status));        
         }
         else {
         	perror("fork");//error
         }

}

char **slice(char *in){ //function to parse the input into an array of strings
	int slices = BREAD_SLICE; //buffer
	char *argument; //string
        char **arguments=malloc(slices * sizeof(char*)); //array of string allocated via malloc
        int a = 0; //counter
	if (!arguments) { //check for array of strings setup
       		printf("allocation error\n");
                exit(EXIT_FAILURE);
       	}

      	argument= strtok(in, BREAD_SLICE_TOK);//read string into array
	//printf("argument> %s \n", argument);
      	while(argument != NULL) //while not null read
      	{	
	//	printf("argument> %s \n", argument);
        	arguments[a] = argument; //read into array of strings
        	a++;
		if (a >= slices) { //make buffer larger if needed
     			 slices += BREAD_SLICE;
     			 arguments = realloc(arguments, slices * sizeof(char*));
     			 if (!arguments) {
       			 	exit(EXIT_FAILURE);
     			 }
  		 }
        	argument = strtok(NULL, BREAD_SLICE_TOK);//next token
     	 }
     	arguments[a]=NULL;//set last to null
	return arguments; //return array of strings	

}

char * bread_read()
{
	int max = BREAD_PAN;
	char * input = malloc(max);
	if(input == 0){
		exit(1); //out of memory.
	}
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
		if (i == max) { /* buffer full */
			printError();
			free(input);
			exit(1);
		}
		i++;
	}

	return input;
}

int toast(char **args){
	char * command = args[0];	
	if(strcmp (command, "exit") == 0)
        {
                exit(0);
        }
        else if( strcmp ( command, "ls" ) == 0 )
        {
                breadLs(args);
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

        else if( strcmp ( command, "cd" ) == 0 ){

                  if(args[1]==NULL){
                      chdir(getenv("HOME"));
                  }
                  else{
                      chdir(args[1]);
                  }
        }

        else
        {
              printError(); //not a valid command.
        }
	return 0;
}
