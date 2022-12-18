#include "../monty.h"

/**
 * pchar - Stack pchar function. Prints the data in the top node as an
 *         ASCII char. Prints error if int isn't a valid ASCII char.
 *
 * @line: Current line number in Monty script (for error handling).
 */
void pchar(int line)
{
	if (!montyStack)
		err(14, line, "");

	if (montyStack->n < 0 || montyStack->n > 127)
		err(15, line, "");

	printf("%c\n", montyStack->n);
}
