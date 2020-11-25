#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 255


char *read_line()
{
	int position = 0;
	char c, *buffer = malloc(sizeof(char));
	
	if(buffer == NULL)
	{
    	printf("Could not allocate memory!");
    	exit(1);
  	}
  
  	// Read input until a new line is hit.
	while((c = getchar()) != '\n')
	{
		// Reallocate buffer if it exceeds
		buffer = realloc(buffer, (sizeof(char)));

		if(buffer == NULL)
		{
			printf("Could not allocate memory!");
			exit(1);
		}

		buffer[position++] = c;
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