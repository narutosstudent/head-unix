#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	FILE *filePointer = NULL;

	bool isFileProvided = argc == 2;
	bool isStdinProvided = argc == 1;
	if (isStdinProvided)
	{
		filePointer = stdin;
	}
	else if (isFileProvided)
	{
		// A file name was provided, so attempt to open it.
		filePointer = fopen(argv[1], "r");
		if (filePointer == NULL)
		{
			// fopen returned NULL, so print an error message and exit.
			fprintf(stderr, "Error opening file: %s\n", argv[1]);
			return 1;
		}
	}
	else
	{
		// More than one argument was provided, so print an error message and exit.
		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		return 1;
	}

	return 0;
}
