#include "../monty.h"

/**
 * add - Stack add function. Merges the top two elements of a stack.
 *
 * @line: Current line number in Monty script (for error handling).
 */
void add(int line)
{
	stack_t *tmpNode = montyStack;

	if (!montyStack || montyStack->next == NULL)
		err(8, line, "");

	montyStack->next->n += montyStack->n;
	montyStack = montyStack->next;
	montyStack->prev = NULL;

	free(tmpNode);
}
