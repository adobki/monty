#include "../monty.h"

/**
 * rotl - Stack rotl function. Rotates the stack at the top. First node becomes
 *        last, and last node becomes the first.
 *
 * Return: EXIT_SUCCESS (0) on success.
 *         EXIT_FAILURE (1) on error.
 */
int rotl()
{
	stack_t *rotlNode = montyStack, *head = montyStack;

	if (!montyStack || montyStack->next == NULL)
		return (EXIT_FAILURE);

	while (head->next)
		head = head->next;

	head->next = rotlNode, rotlNode->prev = head;

	montyStack = montyStack->next;
	montyStack->prev = rotlNode->next = NULL;

	return (EXIT_SUCCESS);
}
