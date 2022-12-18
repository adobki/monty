#include "monty.h"

/**
 * err - Error handler for monty program, for code portability. Function
 *       prints an error message to stderr when a corresponding error is
 *       caught during program execution, flushes the stack (montyStack),
 *       then exits the program with EXIT_FAILURE as the return code.
 *
 * @code: Error code. (See block comments in errMsgs definition below)
 * @line: Line number from the Monty ByteCode script that threw the error.
 * @str: Some string to be printed in the error message.
 */
void err(int code, int line, char *str)
{
	char errMsgs[funcMAX - 1][40] = {
	"USAGE: monty file",                                  /*  0 */
	"Error: Can't open file %s",                          /*  1 */
	"Error: malloc failed",                               /*  2 */
	"L%d: unknown instruction ",                          /*  3 */
	"L%d: usage: push integer",                           /*  4 */
	"L%d: can't pint, stack empty",                       /*  5 */
	"L%d: can't pop an empty stack",                      /*  6 */
	"L%d: can't swap, stack too short",                   /*  7 */
	"L%d: can't add, stack too short",                    /*  8 */
	"L%d: can't sub, stack too short",                    /*  9 */
	"L%d: can't div, stack too short",                    /* 10 */
	"L%d: division by zero",                              /* 11 */
	"L%d: can't mul, stack too short",                    /* 12 */
	"L%d: can't mod, stack too short",                    /* 13 */
	"L%d: can't pchar, stack empty",                      /* 14 */
	"L%d: can't pchar, value out of range",               /* 15 */
	};

	if (code == 1)
		fprintf(stderr, &errMsgs[code][0], str);
	else
	{
		fprintf(stderr, &errMsgs[code][0], line);
		if (code == 3)
			while (*str && *str != ' ' && *str != '\n' && *str != '#')
				fprintf(stderr, "%c", *str++);
	}

	fprintf(stderr, "\n");

	while (montyStack)
		pop(-1);

	exit(EXIT_FAILURE);
}
