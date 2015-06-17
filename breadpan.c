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

int breadLs(char **args);
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
		char **args= slice(input);//create out array of strings to inpuit args...hoping this will work
		status = toast(args);
		//let's free up those buffers.
		free(input);
		free(args);
	}while(status);
	return 0;//safe exit at end of while loop.
}

int breadLs(char **arguments){ //changed this to accept array of strings
	 int status;
         int child = fork();
         if(child == 0){
		//child
       	//	arguments[0] = strdup("/bin/ls");
         	if(execvp(arguments[0], arguments)  == -1) 
			return 0;
         }
         else if (child > 0){
        	 do {
     			 waitpid(child, &status, WUNTRACED);
    		} while (!WIFEXITED(status) && !WIFSIGNALED(status));        
		return 1;
         }
         else {
         	perror("fork");//error
         }
	return 1;
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
      	while(argument != NULL) //while not null read
      	{	
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
	char * input = malloc(sizeof(char) * max);
	int c;
	int position = 0;
	if(input == 0){
 		exit(1); //out of memory.
 	}
	while (1) {
    	// Read a character
    		c = getchar();

   	 // If we hit EOF, replace it with a null character and return.
   		 if (c == EOF || c == '\n') {
      			input[position] = '\0';
      			return input;
    		} else {
      			input[position] = c;
    		}
    		position++;

    	// If we have exceeded the buffer, reallocate.
    		if (position >= max) {
      			max += BREAD_PAN;
      			input = realloc(input, max);
      			if (!input) {
				printError();
        			exit(EXIT_FAILURE);
      			}
    		}
  	} 
	return input;
}

int toast(char **args){
	char * command = args[0];	
//	printf("\n%s\n", command);
	if(strcmp (command, "exit") == 0)
        {
		return 0;
        }
        else if( strcmp ( command, "ls" ) == 0 )
        {
              return breadLs(args);
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
	
	else if(command == NULL){
		return 1;
	}

        else
        {
              printError(); //not a valid command.
        }
	return 1; //exit by default
}
