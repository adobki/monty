#include "../monty.h"

/**
 * pop - Stack pop function. Removes the node at the top of a stack.
 *
 * @line: Current line number in Monty script (for error handling).
 *
 * Return: Data stored in deleted node on success.
 *         -1 on error.
 */
int pop(int line)
{
	stack_t *tmpNode = montyStack;
	int data = -1;

	if (!montyStack)
		err(6, line, "");

	data = montyStack->n;
	if (montyStack->next)
	{
		montyStack = montyStack->next;
		montyStack->prev = NULL;
	}
	else
		montyStack = NULL;

	free(tmpNode);

	return (data);
}
