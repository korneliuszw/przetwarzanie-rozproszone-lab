#include <stack.h>
#include <stdlib.h>

void push(StackNode** stack, int val) {
	StackNode* node = malloc(sizeof(StackNode));
	node->next = *stack;
	node->value = val;
	*stack = node;
}

int pop(StackNode** stack) {
	int val = (*stack)->value;
	StackNode* old = *stack;
	*stack = old->next;
	free(old);
	return val;
}
