#include <stack.h>
#include <utils.h>
#include <stdio.h>
void print_stack(StackNode* node) {
	while (node != NULL) {
		printf("%d ", node->value);
		node = node->next;
	}
	printf("\n");
}
