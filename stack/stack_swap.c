#include "../monty.h"

/**
 * swap - Stack swap function. Swaps the top two elements of a stack.
 *
 * @line: Current line number in Monty script (for error handling).
 */
void swap(int line)
{
	int tmpData;

	if (!montyStack || montyStack->next == NULL)
		err(7, line, "");

	tmpData = montyStack->n;
	montyStack->n = montyStack->next->n;
	montyStack->next->n = tmpData;
}
