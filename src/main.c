#include <stdio.h> 		// For: printf(), fprintf(), getchar(), perror(), stderr
#include <stdlib.h> 	// For: malloc(), realloc(), free(), exit(), execvp(), EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> 	// For: strtok(), strcmp(), strcat(), strcpy()
#include <sys/types.h>
#include <unistd.h> 	// For: chdir(), fork(), exec(), pid_t, getcwd()
#include <sys/wait.h> 

#define BUFFER_SIZE_LINE 1
#define TOKEN_DELIMITER " \t\r\n\a"
#define BUFFER_SIZE_TOKEN 1

/* 
 * Builtin command name
*/
char *builtin_str[] = {"cd", "exit", "help"};

/* 
 * Function: shell_cd
 * 
 * Changes current working directory
 * 
 * args: arguments to the cd command, will consider only the first argument after the command name 
*/
int shell_cd(char **args)
{
	if(args[1] == NULL)
		fprintf(stderr, "lsh: expected argument to \n cd \n");
	else if (chdir(args[1]) < 0)
		perror("lsh error"); 
	return 1;
}

/*
 * Function:  shell_exit
 * 
 * Exits from the shell
 *
 * return: status 0 to indicate termination
 */
int shell_exit(char ** args)
{
	return 0;
}


/*
 * Function:  split_line
 * 
 * Splits a line into tokens using strtok()
 *
 * line: a line read from terminal
 *
 * returns: an array of pointers to individual tokens
 */
char **sh_split_line(char *line)
{
	int position = 0, buffer_size = BUFFER_SIZE_TOKEN;
	char *token;
	//pointer to an array which holds pointer(address) to the first character of the token
	char **tokens = malloc(sizeof(char*) * buffer_size);

	if(tokens == NULL)
	{
		fprintf(stderr, "Allocation error.\n");
		exit(1);
	}

	token = strtok(line, TOKEN_DELIMITER);
	while(token != NULL)
	{
		tokens[position++] = token;
		if(position == buffer_size)
		{
			buffer_size += position;
			tokens = realloc(tokens, sizeof(char*) * buffer_size);
			if(tokens == NULL)
			{
				fprintf(stderr, "Allocation Error.\n");
			}
		}
		token = strtok(NULL, TOKEN_DELIMITER);
	}
	tokens[position] = NULL;
	return tokens;
}

/*
 * Function:  read_line
 * 
 * reads a line from terminal
 *
 * returns: a line read from terminal
 */
char *sh_read_line()
{
	int position = 0, c, buffer_size = BUFFER_SIZE_LINE;
	char *buffer = malloc(sizeof(char) * buffer_size);

	if(buffer == NULL)
	{
		fprintf(stderr, "Allocation Error.\n");
	}

	while(EOF != (c=getchar()) && c != '\n')
	{
		buffer[position++] = c;
		if(position == buffer_size)
		{
			buffer_size += position;
			buffer = realloc(buffer, sizeof(char) * buffer_size);
			if(buffer == NULL)
			{
				fprintf(stderr, "Allocation Error.\n");
			}
		}
	}
	buffer[position] = '\0';
	return buffer;
}

/*
 * Function:  start_process
 * 
 * starts and executes a process for a command
 *
 * args: arguments tokenized from the command line
 *
 * return: status 1
 */
int sh_launch_process(char **args)
{
	pid_t pid, wpid;
	pid = fork();
	if(pid < 0)
		// error forking			
		fprintf(stderr, "failed to create a process");
	else if(pid == 0) 
		// child process
		execvp(args[0], args); // replaces the child process to execute the command provied by the user
	else
	{
		// parent process
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED)
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		
	}
	return 1;
}

void shell_loop()
{
	char *line, **args;
	int status; 
	do
	{
		printf(">>");
		line = sh_read_line();
		args = sh_split_line(line);
		status = sh_execute(args);

		free(line);
		free(args);
	} while (status);
	
}

int main()
{
	// Run command loop
	shell_loop();
	return 0;
}