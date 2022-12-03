#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const char* readFile(const char*);
const char** getLines(const char*);

int main (int argc, char** argv)
{
	//get lines from file
	assert(argc == 2);
	const char* input = readFile(argv[1]);
	const char** lines = getLines(input);

	free((void*)input);

	long maxsum = 0;
	long sum = 0;
	size_t i = 0;
	while (lines[i] != NULL)
	{
		if (strcmp(lines[i], "") == 0)
		{
			if (sum > maxsum) maxsum = sum;
			sum = 0;
		}
		sum += strtol(lines[i], NULL, 10);
		++i;
	}
	printf("%ld\n", maxsum);
}

//read file contents to string
const char* readFile(const char* fileName)
{
	//open file
	FILE* inputFile = fopen(fileName, "r");
	assert(inputFile != NULL);

	//get file size
	fseek(inputFile, 0L, SEEK_END);
	size_t fileSize = ftell(inputFile);
	rewind(inputFile); 

	//store contents on the heap
	const char* fileContents = (char*)malloc(fileSize);
	fread((void*)fileContents, fileSize, 1, inputFile);
	fclose(inputFile);

	return fileContents;
}

//split string on newline
const char** getLines(const char* string)
{
	char** lines;	
	size_t lineCount = 1;

	char* line;
	char* start = (char*)string;
	size_t length = 0;

	while (*start != '\0')
	{
		//get length of line
		length = 0;
		while (start[length] != '\n')
		{
			++length;
		}

		//store line on heap
		line = malloc(sizeof(char) * length + 1);
		strncpy(line, start, length);
		line[length] = '\0';

		
		//add line to lines array
		lines = realloc(lines, sizeof(char*) * lineCount);
		lines[lineCount++ - 1] = line;

		//consume line
		start += length + 1;
	}

	//null terminate lines array
	lines = realloc(lines, sizeof(char*) * lineCount);
	lines[lineCount -1] = NULL;

	return (const char**)lines;
}
