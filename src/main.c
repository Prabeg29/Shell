#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 255
#define TOKEN_DELIMITER " \t\r\n\a"

/*
 * Function:  split_line
 * -----------------------------
 *  splits a line into tokens using strtok()
 *
 * line: a line read from terminal
 *
 * returns: an array of pointers to individual tokens
 */
/* char **split_line(char *line)
{
	int position = 0;
	char *token;
	// pointer to an array which holds pointer(address) to the first character of the token
	char **tokens = malloc(sizeof(char*) * 1);

	if(!tokens)
	{
		fprintf(stderr, "allocation error.\n");
		exit(1);
	}

	token = strtok(line, TOKEN_DELIMITER);
	while(token != NULL)
	{
		tokens[position++] = token;
		tokens = realloc(tokens, sizeof(char*) * 1);

		if(tokens == NULL)
		{
			fprintf(stderr, "allocation error.\n");
			exit(1);
		}
		token = strtok(NULL, TOKEN_DELIMITER);
	}
	tokens[position] = NULL;
	return tokens;
} */

/*
 * Function:  read_line
 * ----------------------------
 * reads a line from terminal
 *
 * returns: a line read from terminal
 */
char *read_line()
{
	int position = 0, c, buffer_size = 10;
	char *buffer = malloc(sizeof(char) * buffer_size);

	if(buffer == NULL)
	{
		fprintf(stderr, "Allocation Error.\n");
	}

	while(EOF != (c=getch()) && c != '\n')
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
	char *line; // **arguments;
	do
	{
		printf(">>");
		line = read_line();
		//arguments = split_line(line);
	} while (1);
	
}

int main()
{
	// Run command loop
	shell_loop();
	return 0;
}