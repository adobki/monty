#include "../monty.h"

/**
 * top - Stack pall and pint function. Prints the data in all the nodes from
 *       top to bottom node (pall) or the top node (pint) in a stack.
 *       NOTE: Mode 1==pall (print all nodes), Mode 0==pint (print top node)
 *
 * @mode: What to print (see note above).
 * @line: Current line number in Monty script (for error handling).
 *
 * Return: Number of nodes printed from Monty stack.
 */
int top(int mode, int line)
{
	stack_t *head = montyStack;
	int countr = 0;

	if (mode)
	{
		while (head)
			printf("%d\n", head->n), head = head->next, countr++;
	}
	else
	{
		if (!head)
			err(5, line, "");

		printf("%d\n", head->n);
	}

	return (countr);
}
