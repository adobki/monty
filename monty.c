#include "monty.h"

stack_t *montyStack = NULL;

/**
 * main - Program is an interpreter for Monty ByteCodes files. It reads and
 *        executes commands in the file line by line. The commands, in this
 *        case, carry out standard operations on a stack, montyStack, which
 *        is a pointer to a doubly linked list [and a global variable].
 *
 * @argc: Number of arguments passed to program from the commandline (CL)
 * @argv: Vector of all arguments passed to prongram from CL.
 *
 * Return: EXIT_SUCCESS (0) on success.
 *         EXIT_FAILURE (1) on error.
 */
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	readFile(argv[1]);

	while (montyStack)
		pop(-1);

	return (EXIT_SUCCESS);
}

/**
 * readFile - Function that opens and reads all lines from a text file.
 *
 * @filename: Text file to be opened/read.
 *
 * Return: Number of lines read by function on success.
 *         0 on error, filename==NULL, or file is empty.
 */

ssize_t readFile(const char *filename)
{
	char *buffer;
	FILE *FP;
	ssize_t line = 0, size = 99;

	FP = fopen(filename, "r");
	if (FP == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	buffer = malloc(sizeof(char) * size);
	if (!buffer)
		err(1, line, "");

	while (1)
	{
		buffer = fgets(buffer, size, FP);
		if (!buffer)
			break;
		while (*buffer == ' ')
			buffer++;
		runLine(buffer, ++line);
	}

	fclose(FP);
	free(buffer);

	return (line);
}

/**
 * runLine - Executes a line from a Monty ByteCode script. First, it processes
 *           the line to check for a valid command. If a command is found and
 *           its syntax is valid, command is executed by calling a function.
 *
 * @str: Line from a Monty ByteCode script to be run by function.
 * @line: Line number of str from the Monty ByteCode script.
 *
 * Return: EXIT_SUCCESS (0) on success.
 *         EXIT_FAILURE (1) on error.
 */
int runLine(char *str, int line)
{
	int i, callFunc;

	if (*str == 0 || *str == '\n')
		return (EXIT_SUCCESS);

	i = 1, callFunc = 0;

	if (*str == 'p')
	{
		if (str[i] == 'u' && str[i + 1] == 's' && str[i + 2] == 'h')
			callFunc = 2, str += 4;
		else if (str[i] == 'a' && str[i + 1] == 'l' && str[i + 2] == 'l')
			callFunc = 1, str += 4;
		else if (str[i] == 'i' && str[i + 1] == 'n' && str[i + 2] == 't')
			callFunc = 3, str += 4;
		else if (str[i] == 'o' && str[i + 1] == 'p')
			callFunc = 4, str += 3;
	}
	else if (*str == 's')
	{
		if (str[i] == 'w' && str[i + 1] == 'a' && str[i + 2] == 'p')
			callFunc = 5, str += 4;
	}
	else if (str[0] == 'n' && str[i] == 'o' && str[i + 1] == 'p')
		return (EXIT_SUCCESS);
	else if (str[0] == 'a' && str[i] == 'd' && str[i + 1] == 'd')
		callFunc = 6, str += 3;
	else
		err(2, line, str);

	if (*str == ' ' || *str == '\n' || *str == '\0')
	{
		if (callFunc == 1)
			top(1, line);
		else if (callFunc == 2)
		{
			while (*str == ' ')
				str++;
			if ((*str >= '0' && *str <= '9') || *str == '-')
				push(atoi(str));
			else
				err(3, line, "");
		}
		else if (callFunc == 3)
			top(0, line);
		else if (callFunc == 4)
			pop(line);
		else if (callFunc == 5)
			swap(line);
		else if (callFunc == 6)
			add(line);
	}
	else
		err(2, line, str);

	return (EXIT_SUCCESS);
}

/**
 * err - Error handler for monty program, for code portability.
 *       ERROR CODES:
 *            Code 1:
 *            Code 2: Invalid instruction/command in current line.
 *            Code 3: No/invalid argument given for push command.
 *
 * @code: Error code (see chart above).
 * @line: Line number from the Monty ByteCode script that threw the error.
 * @str: Some string to be printed in the error message.
 *
 * Return: EXIT_SUCCESS (0) on success.
 *         EXIT_FAILURE (1) on error.
 */
void err(int code, int line, char *str)
{
	if (code == 1)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	else if (code == 2)
	{
		fprintf(stderr, "L%d: unknown instruction %s", line, str);
		/* Fixes double new line when str ends with '\n': */
		while (*str)
			str++;
		if (str[-1] != '\n')
			fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}

	else if (code == 3)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line);
		exit(EXIT_FAILURE);
	}

	else if (code == 4)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line);
		exit(EXIT_FAILURE);
	}

	else if (code == 5)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line);
		exit(EXIT_FAILURE);
	}

	else if (code == 6)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line);
		exit(EXIT_FAILURE);
	}

	else if (code == 7)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line);
		exit(EXIT_FAILURE);
	}
}
