#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *montyStack;

void err(int, int, char *);
ssize_t readFile(const char *);
int runLine(char *, int);
int compare(int, char *, char *);
void callFunc(int, int);

#define funcMAX 18
#define bufferSize 999

void push(int);
int top(int, int);
int pop(int);
void swap(int);
void add(int);
void sub(int);
void _div(int);
void mod(int);
void pchar(int);
int pstr(void);
int rotl(void);
int rotr(void);

#endif /* MONTY_H */
