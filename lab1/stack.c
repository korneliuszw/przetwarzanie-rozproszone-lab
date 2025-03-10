#include <stdio.h>
#include <stdlib.h>

/*
    !!! IMPORTANT !!!
    How to compile and execute:
    gcc -Wall -fsanitize=leak -pedantic -o stack stack.c && ./stack
*/

/*
    TODO:
    1. - define a struct for the stack node
    2. - define function to push a value onto the stack
    3. - define function to pop last value from top of the stack
    4. - test how the stack performs on the test cases (You can provide your own)
*/

typedef struct StackNode {
    // here define data stored and pointer to next node

} StackNode;

void push(StackNode** top, int value) {
    /*
        TODO:
        1. - create new stack node (and allocate memory using malloc())
        2. - check if new stack node is NULL, if yes (malloc fail), return error
        3. - set node data
        4. - make pointer defined in StackNode point to the previous top
        5. - assign the top pointer to the new node
    */

}

int pop(StackNode** top) {
    /*
        TODO:
        1. - check if top of the stack is NULL, if yes, return
        2. - pop the top node and return its data
        3. - move the top pointer (store it in temporary data) and retrieve its data
        4. - free the memory of the popped node (use free())
    */

}

void print_stack(StackNode* top) {
    /*
        TODO:
        1. check if top of the stack is empty, if yes, return
        2. write 'while' loop that will print all values from top to bottom
    */

}


int main() {
    // initialize the stack as empty
    StackNode* stack = NULL;
    
    // some 'test cases' to check functionality
    // pushing some values onto the stack
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
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
