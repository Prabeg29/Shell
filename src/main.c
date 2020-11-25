#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 255


char *read_line()
{
	int position = 0, c;
	char *buffer = malloc(sizeof(char) * BUFSIZE);

	// Read character until a new line oe EOF is encountered
	while((c = getchar()) != '\n' || (c = getchar()) != EOF)
	{
		// If we have exceeded the buffer, reallocate.
		buffer = realloc(buffer, sizeof(char) * BUFSIZE);
		buffer[position++] = c;
		if (!buffer) 
		{
        	fprintf(stderr, "shell: allocation error\n");
        	exit(EXIT_FAILURE);
      	}
	}
	buffer[position] = '\0';
	return buffer;
}

void shell_loop()
{
	char *line;
	do
	{
		printf(">>");
		line = read_line();
	} while (1);
	
}

int main()
{
	// Run command loop
	shell_loop();
	return 0;
}