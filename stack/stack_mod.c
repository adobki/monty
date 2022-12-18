#include "../monty.h"

/**
 * mod - Stack mod function. Merges the top two elements of a stack by
 *       dividing the data in the second top element by the top one.
 *       The modulus (remainder) of the division is what is stored.
 *
 * @line: Current line number in Monty script (for error handling).
 */
void mod(int line)
{
	stack_t *tmpNode = montyStack;

	if (!montyStack || montyStack->next == NULL)
		err(13, line, "");

	if (montyStack->n == 0)
		err(11, line, "");

	montyStack->next->n %= montyStack->n;
	montyStack = montyStack->next;
	montyStack->prev = NULL;

	free(tmpNode);
}
