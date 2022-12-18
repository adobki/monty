#include "../monty.h"

/**
 * push - Stack push function. Adds a new node to the top of a stack.
 *
 * @data: Integer data to be stored in the new node.
 */
void push(int data)
{
	stack_t *newNode;

	newNode = malloc(sizeof(stack_t));
	if (!newNode)
		err(2, 0, "");
	newNode->n = data;
	newNode->prev = newNode->next = NULL;

	if (montyStack)
		newNode->next = montyStack, montyStack->prev = newNode;

	montyStack = newNode;
}
