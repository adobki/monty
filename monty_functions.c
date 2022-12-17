#include "monty.h"

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
