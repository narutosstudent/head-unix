#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Needed for strcmp

int main(int argc, char *argv[])
{
	FILE *filePointer = NULL;
	int numLines = 10; // Default number of lines
	bool n_option_provided = false;

	// Loop through all arguments to find '-n' option and filename
	for (int i = 1; i < argc; ++i)
	{
		// Check for '-n' option
		if (strcmp(argv[i], "-n") == 0)
		{
			if (i + 1 < argc)
			{ // Make sure there is another argument after '-n'
				long val;
				char *next_char;
				val = strtol(argv[i + 1], &next_char, 10); // More robust than atoi
				if (*next_char != '\0' || val <= 0)
				{ // Check for valid positive integer
					fprintf(stderr, "Invalid number of lines: %s\n", argv[i + 1]);
					return 1;
				}
				numLines = val;
				n_option_provided = true;
				i++; // Skip the next argument as it is part of '-n'
			}
			else
			{
				fprintf(stderr, "Missing number of lines after -n\n");
				return 1;
			}
		}
		else
		{
			// Argument is not '-n', treat it as a filename
			filePointer = fopen(argv[i], "r");
			if (filePointer == NULL)
			{
				fprintf(stderr, "Error opening file: %s\n", argv[i]);
				return 1;
			}
			break; // Stop processing arguments after finding the file
		}
	}

	if (!filePointer)
	{
		fprintf(stderr, "No file provided\n");
		return 1;
	}

	const int MAX_LINE_LENGTH = 1024;
	char buffer[MAX_LINE_LENGTH];
	int lineCounter = 0;

	// Read and print the specified number of lines
	while (lineCounter < numLines)
	{
		if (fgets(buffer, MAX_LINE_LENGTH, filePointer) == NULL)
		{
			if (feof(filePointer))
			{
				break; // Reached end of file
			}
			if (ferror(filePointer))
			{
				fprintf(stderr, "Error reading file: %s\n", argv[argc - 1]);
				fclose(filePointer);
				return 1;
			}
		}
		else
		{
			printf("%s", buffer);
			lineCounter++;
		}
	}

	// Close the file if it was opened
	if (filePointer && fclose(filePointer) != 0)
	{
		fprintf(stderr, "Error closing file: %s\n", argv[argc - 1]);
		return 1;
	}

	return 0;
}
