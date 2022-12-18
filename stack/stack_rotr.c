#include "../monty.h"

/**
 * rotr - Stack rotr function. Removes the node at the top of a stack.
 *
 * Return: EXIT_SUCCESS (0) on success.
 *         EXIT_FAILURE (1) on error.
 */
int rotr()
{
	stack_t *head = montyStack;

	if (!montyStack || montyStack->next == NULL)
		return (EXIT_FAILURE);

	while (head->next)
		head = head->next;

	head->next = montyStack, head->prev = head->prev->next = NULL;

	montyStack->prev = head, montyStack = head;

	return (EXIT_SUCCESS);
}
