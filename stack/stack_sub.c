#include "../monty.h"

/**
 * sub - Stack sub function. Merges the top two elements of a stack
 *       by subtracting the top element from the second.
 *
 * @line: Current line number in Monty script (for error handling).
 */
void sub(int line)
{
	stack_t *tmpNode = montyStack;

	if (!montyStack || montyStack->next == NULL)
		err(9, line, "");

	montyStack->next->n -= montyStack->n;
	montyStack = montyStack->next;
	montyStack->prev = NULL;

	free(tmpNode);
}
