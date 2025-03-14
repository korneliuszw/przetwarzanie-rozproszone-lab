/*
    TODO:
    1. - define a struct for the stack node
    2. - declare function to push a value onto the stack
    3. - declare function to pop last value from top of the stack

*/

#ifndef STACK_NODE
#define STACK_NODE

typedef struct StackNode {
	int value;
	struct StackNode* next;
} StackNode;

void push(StackNode** stack, int val);

int pop(StackNode** stack);

#endif
