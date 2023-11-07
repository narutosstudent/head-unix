#include <stdio.h>

int main(int argc, char *argv[])
{
	// Initialize a file pointer to NULL. This will be used to refer to the file if one is provided.
	FILE *filePointer = NULL;

	// 1. Check if command line arguments are provided.
	// argc counts how many arguments. If argc is 1, no file name was provided.
	// argv contains the actual arguments; argv[0] is the program name, argv[1] would be the first argument.

	if (argc == 1)
	{
		filePointer = stdin;
	}
	else if (argc == 2)
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
