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
//basic error handling from assignment sheet
#define grepPat " \t\r\n\a" //defined a grep pattern
#define buffer 64 //define buffer size
void printError(){
	char error_message[30] = "An error has occurred\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

void breadLs(char *arguments[]);
<<<<<<< Updated upstream
char **parse(char *in);
=======
char *bread_read();
>>>>>>> Stashed changes

int main(int argc, char *argv[])
{
	char* input; /* allocate buffer */

  	//start a loop that will run until a user enters "exit"
  	while(1) //will run forever unless we tell it to quit.
	{
		printf("breadpan$> "); //shell prompt

		//no we have our input as a string, time to start parsing it out and switching between commands.
<<<<<<< Updated upstream
		char * command = strtok(input, grepPat);
		//printf("\n command entered: %s \n", command);
=======
		input = bread_read();
		char * command = strtok(input, " ");
//		printf("\n command entered: %s \n", command);

		char *arguments[10];
                int a = 0;
		arguments[a] = strtok( NULL , " " );
                while(arguments[a] != NULL)
                {
                        a++;
			if(a > 10)
				break;
                        arguments[a] = strtok( NULL , " " );
                }

>>>>>>> Stashed changes
		//we can't use a switch because C is retarded.
		//so here's our if else if bucket code
		char **args= parse(input);//create out array of strings to inpuit args...hoping this will work
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
	}
	exit(0); //safe exit at end of while loop.
}

void breadLs(char **arguments){ //changed this to accept array of strings
	 int i = 1;
	 int j = 1;
         int child = fork();
         if(child == 0){
	         char *argv[11];//stack allocated array
        	 argv[0] = strdup("/bin/ls");
       		 while(arguments[j] !=NULL){ //the arguments are in an array 1 shorter than the one we are building. i starts at 1 instead of 0
         		argv[i] = arguments[j];
         		i++;
         		j++;
         	}
         	argv[i] = NULL;// terminate command
         	printf("arg 1 = %s \n", arguments[1]);//test for proper setup
         	execvp(argv[0],argv);
		printError();
		exit(0);
         }

         else if (child > 0){
         	wait(NULL);//wait until complete        
         }

         else {
         	perror("fork");//error
         }

}

<<<<<<< Updated upstream

char **parse(char *in){ //function to parse the input into an array of strings
	int argbuffer= buffer; //buffer
	char *argument; //string
        char **arguments=malloc(argbuffer * sizeof(char*)); //array of string allocated via malloc
        int a = 0; //counter
	if (!arguments) { //check for array of strings setup
       		printf("allocation error\n");
                exit(EXIT_FAILURE);
       	}

      	argument= strtok(in, grepPat);//read string into array
      	while(argument!= NULL) //while not null read
      	{	

        	arguments[a] = argument; //read into array of strings
        	a++;
		if (a >=argbuffer) { //make buffer larger if needed
     			 argbuffer += buffer;
     			 arguments = realloc(arguments, argbuffer * sizeof(char*));
     			 if (!arguments) {
       			 exit(EXIT_FAILURE);
     			 }
  		 }
        	argument = strtok(NULL, grepPat);//next token
     	 }
     	arguments[a]=NULL;//set last to null
	return arguments; //return array of strings	

}
=======
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

>>>>>>> Stashed changes
