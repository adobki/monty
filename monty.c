#include "monty.h"
#define bufferSize 999

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
		err(0, -1, "");

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
	char buffer[bufferSize];
	FILE *FP;
	ssize_t index, line = 0;

	FP = fopen(filename, "r");
	if (FP == NULL)
		err(1, -1, (char *)filename);

	while (1)
	{
		index = 0;
		if (!fgets(&buffer[index], bufferSize, FP))
			break;
		while (buffer[index] == ' ')
			index++;
		if (runLine(&buffer[index], ++line))
		{
			line = EXIT_FAILURE;
			break;
		}
	}

	fclose(FP);

	return (line);
}

/**
 * compare - Runs a comparison operation based on selected mode.
 *           * mode == 1:
 *             Compares two strings. Checks if the word in str is the first
 *             word in src. Returns index of command (in montyCom array) and
 *             number of letters in the command if true, 0 otherwise.
 *           * mode == 2:
 *             Checks that every character in the first word of string is an
 *             integer (isInt function), for passing it to atoi() function.
 *             NOTE: Check skips first character if it's negative sign: '-'.
 *
 * @mode: Determines comparison method. See notes above.
 * @str: Command from stored list of valid Monty ByteCode script commands.
 * @src: Line from a Monty ByteCode script to be checked for a command.
 *
 * Return: Number of letters in src if true on success.
 *         0 on error.
 */
int compare(int mode, char *str, char *src)
{
	int index = -1;

	if (mode == 1)
	{
		while (str[++index])
			if (str[index] != src[index])
				return (0);

		if (src[index] != ' ' && src[index] != '\n' && src[index] != '\0')
			index = 0;
	}
	else if (mode == 2)
	{
		while (str[++index] && str[index] != ' ' && str[index] != '\n')
			if (str[index] < '0' || str[index] > '9')
				if (index != 0 || str[index] != '-')
					return (0);
		if (*src == '-' && index == 1)
			return (0);
	}
	else
		return (0);

	return (index);
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
	int len, callFunc = 7;
	char comList[7][5] = {"push", "pall", "pint", "pop", "swap", "nop", "add"};

	if (*str == 0 || *str == '\n')
		return (EXIT_SUCCESS);
	while (callFunc--)
	{
		len = compare(1, comList[callFunc], str);
		if (len)
			break;
	}
	if (!len)
		err(3, line, str);
	else
		str += len;

callFunc++;	/* ADD new function at 0 index and delete this line. Thank you! */
	if (callFunc == 1)
	{
		while (*str == ' ')
			str++;
		if (compare(2, str, str))
			push(atoi(str));
		else
			err(4, line, "");
	}
	else if (callFunc == 2)
		top(1, line);
	else if (callFunc == 3)
		top(0, line);
	else if (callFunc == 4)
		pop(line);
	else if (callFunc == 5)
		swap(line);
	else if (callFunc == 6)
		return (EXIT_SUCCESS);
	else if (callFunc == 7)
		add(line);

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
 */
void err(int code, int line, char *str)
{
	char errMsgs[9][50] = {
	"USAGE: monty file",                                  /*  0 */
	"Error: Can't open file %s",                          /*  1 */
	"Error: malloc failed",                               /*  2 */
	"L%d: unknown instruction ",                          /*  3 */
	"L%d: usage: push integer",                           /*  4 */
	"L%d: can't pint, stack empty",                       /*  5 */
	"L%d: can't pop an empty stack",                      /*  6 */
	"L%d: can't swap, stack too short",                   /*  7 */
	"L%d: can't add, stack too short",                    /*  8 */
	};

	if (code == 1)
		fprintf(stderr, &errMsgs[code][0], str);
	else if (errMsgs[code][0] == 'L')
	{
		fprintf(stderr, &errMsgs[code][0], line);
		if (code == 3)
			while (*str && *str != ' ' && *str != '\n' && *str != '\t')
				fprintf(stderr, "%c", *str++);
	}
	else
		fprintf(stderr, &errMsgs[code][0]);

	fprintf(stderr, "\n");

	while (montyStack)
		pop(-1);

	exit(EXIT_FAILURE);
}
