#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/pqueue.h"

void qinsert(pqueue **phead, void *data, int k) {
    pqueue *new_node = (pqueue *)malloc(sizeof(pqueue));
    if (!new_node) {
        perror("Failed to allocate memory for new node");
        return;
    }
    
    new_node->data = data;
    new_node->k = k;
    new_node->next = NULL;
    new_node->prev = NULL;
    
    // If list is empty
    if (*phead == NULL) {
        *phead = new_node;
        return;
    }
    
    // If new node has higher priority than head
    if (k < (*phead)->k) {
        new_node->next = *phead;
        (*phead)->prev = new_node;
        *phead = new_node;
        return;
    }
    
    // Find position for new node
    pqueue *current = *phead;
    while (current->next != NULL && current->next->k <= k) {
        current = current->next;
    }
    
    // Insert new node
    new_node->next = current->next;
    if (current->next != NULL) {
        current->next->prev = new_node;
    }
    current->next = new_node;
    new_node->prev = current;
}

void qlist(pqueue *head, void (*print_data)(void *)) {
    pqueue *current = head;
    while (current != NULL) {
        printf("Priority: %d, Data: ", current->k);
        if (print_data) {
            print_data(current->data);
        } else {
            printf("%p", current->data);
        }
        printf("\n");
        current = current->next;
    }
}

void qremove(pqueue **phead, int k) {
    if (*phead == NULL) {
        return;
    }
    
    pqueue *current = *phead;
    
    // If head is to be removed
    if (current->k == k) {
        *phead = current->next;
        if (*phead != NULL) {
            (*phead)->prev = NULL;
        }
        free(current);
        return;
    }
    
    // Find node with priority k
    while (current != NULL && current->k != k) {
        current = current->next;
    }
    
    // If node was not found
    if (current == NULL) {
        return;
    }
    
    // Remove node
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    
    free(current);
}

pqueue *qpop(pqueue **phead) {
    if (*phead == NULL) {
        return NULL;
    }
    
    pqueue *popped = *phead;
    *phead = popped->next;
    
    if (*phead != NULL) {
        (*phead)->prev = NULL;
    }
    
    popped->next = NULL;
    popped->prev = NULL;
    
    return popped;
}

void qserialize(pqueue *head, size_t ndata, char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    
    pqueue *current = head;
    while (current != NULL) {
        fwrite(&(current->k), sizeof(int), 1, file);
        fwrite(current->data, ndata, 1, file);
        current = current->next;
    }
    
    fclose(file);
}

void qunserialize(pqueue **phead, size_t ndata, char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return;
    }
    
    int k;
    void *data;
    
    while (fread(&k, sizeof(int), 1, file) == 1) {
        data = malloc(ndata);
        if (!data) {
            perror("Failed to allocate memory for data");
            fclose(file);
            return;
        }
        
        if (fread(data, ndata, 1, file) != 1) {
            free(data);
            break;
        }
        
        qinsert(phead, data, k);
    }
    
    fclose(file);
} 