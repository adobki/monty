#include "../monty.h"

/**
 * mul - Stack mul function. Merges the top two elements of a stack by
 *       multiplying the data in the top element by the second one.
 *
 * @line: Current line number in Monty script (for error handling).
 */
void mul(int line)
{
	stack_t *tmpNode = montyStack;

	if (!montyStack || montyStack->next == NULL)
		err(12, line, "");

	montyStack->next->n *= montyStack->n;
	montyStack = montyStack->next;
	montyStack->prev = NULL;

	free(tmpNode);
}
