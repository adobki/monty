#include "monty.h"

#ifndef STACK_H
#define STACK_H

#include "stack/stack_add.c"
#include "stack/stack_div.c"
#include "stack/stack_mod.c"
#include "stack/stack_mul.c"
#include "stack/stack_pchar.c"
#include "stack/stack_pop.c"
#include "stack/stack_pstr.c"
#include "stack/stack_push.c"
#include "stack/stack_rotl.c"
#include "stack/stack_rotr.c"
#include "stack/stack_sub.c"
#include "stack/stack_swap.c"
#include "stack/stack_top.c"

#endif /* STACK_H */

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
	int len, func = funcMAX;
	char comList[funcMAX][6] = {"push", "pall", "pint", "pop", "swap", "nop",
	"add", "sub", "div", "mul", "mod", "pchar", "pstr", "rotl", "rotr",
	"stack", "queue", "#"};

	if (*str == 0 || *str == '\n' || *str == '#')
		return (EXIT_SUCCESS);
	while (func--)
	{
		len = compare(1, comList[func], str);
		if (len)
			break;
	}
	if (!len)
		err(3, line, str);

	if (func == 0)
	{
		str += len;
		while (*str == ' ')
			str++;
		if (*str != '#' && compare(2, str, str))
			push(atoi(str));
		else
			err(4, line, "");
	}
	else
		callFunc(func, line);

	return (EXIT_SUCCESS);
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
		if (*src == '#')
			return (1);

		while (str[++index])
			if (str[index] != src[index])
				return (0);

		if (src[index] != ' ' && src[index] != '\n' && src[index] != '\0')
			if (src[index] != '#')
				index = 0;
	}
	else if (mode == 2)
	{
		while (str[++index] && str[index] != ' ' && str[index] != '\n')
		{
			if (str[index] < '0' || str[index] > '9')
				if (index != 0 || str[index] != '-')
					return (0);
			if (str[index + 1] == '#')
				return (++index);
		}
		if ((*src == '-' || *src == '#') && index == 1)
			return (0);
	}
	else
		return (0);

	return (index);
}

/**
 * callFunc - Calls a function to perform a Monty stack operation.
 *            Truncated from runLine function for <= 40 lines rule.
 *
 * @func: Index of function to be called.
 * @line: Current line number in the Monty ByteCode script.
 */
void callFunc(int func, int line)
{
	if (func == 1)
		top(1, line);
	else if (func == 2)
		top(0, line);
	else if (func == 3)
		pop(line);
	else if (func == 4)
		swap(line);
	else if (func == 5 || func == funcMAX - 1)
		return;
	else if (func == 6)
		add(line);
	else if (func == 7)
		sub(line);
	else if (func == 8)
		_div(line);
	else if (func == 9)
		mul(line);
	else if (func == 10)
		mod(line);
	else if (func == 11)
		pchar(line);
	else if (func == 12)
		pstr();
	else if (func == 13)
		rotl();
	else if (func == 14)
		rotr();
	else if (func >= 15)
		return;
}

