#include <stdlib.h>
#include <stack.h>
#include <utils.h>

int main() {
    // initialize the stack as empty
    StackNode* stack = NULL;

    // some 'test cases' to check functionality
    // pushing some values onto the stack
    push(&stack, 10);
    push(&stack, 40);
    push(&stack, 55);
    print_stack(stack);
    
    // popping values from the stack
    pop(&stack);
    print_stack(stack);
    pop(&stack);
    print_stack(stack);
    pop(&stack);
    print_stack(stack);

    return 0;
}
