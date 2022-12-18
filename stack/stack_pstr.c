#include "../monty.h"

/**
 * pstr - Stack pstr function. Prints the data in each node as an
 *        ASCII char. Simply stops printing on error.
 *
 * @line: Current line number in Monty script (for error handling).
 *
 * Return: Number of nodes printed from Monty stack.
 */
int pstr(void)
{
	stack_t *head = montyStack;
	int countr = 0;

	while (head)
	{
		if (head->n < 7 || head->n > 127)
			break;

		printf("%c", head->n);
		head = head->next, countr++;
	}

	printf("\n");

	return (countr);
}
