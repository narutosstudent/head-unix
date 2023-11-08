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
		filePointer = fopen(argv[1], "r");
		if (filePointer == NULL)
		{
			fprintf(stderr, "Error opening file: %s\n", argv[1]);
			return 1;
		}
	}
	else
	{
		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		return 1;
	}

	const int MAX_LINE_LENGTH = 1024; // Adjust the line length as needed
	const int MAX_LINES = 10;
	char buffer[MAX_LINE_LENGTH];
	int lineCounter = 0;

	while (lineCounter < MAX_LINES)
	{
		if (fgets(buffer, MAX_LINE_LENGTH, filePointer) == NULL)
		{
			if (feof(filePointer))
			{
				// End of file reached, break out of the loop.
				break;
			}
			if (ferror(filePointer))
			{
				// An error occurred while reading the file.
				fprintf(stderr, "Error reading file: %s\n", isFileProvided ? argv[1] : "standard input");
				fclose(filePointer);
				return 1;
			}
		}
		else
		{
			// Successfully read a line, so print it.
			printf("%s", buffer);
			lineCounter++;
		}
	}

	if (isFileProvided && fclose(filePointer) != 0)
	{
		fprintf(stderr, "Error closing file: %s\n", argv[1]);
		return 1;
	}

	return 0;
}