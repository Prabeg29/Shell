#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE_LINE 1
#define TOKEN_DELIMITER " \t\r\n\a"
#define BUFFER_SIZE_TOKEN 1

/*
 * Function:  split_line
 * -----------------------------
 * splits a line into tokens using strtok()
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
 * ----------------------------
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