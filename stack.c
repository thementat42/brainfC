/**
 * @file stack.c
 * The implementation of the stack structure
 * @see stack.h
 */

#include "stack.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

stack* createStack() {
    stack* s = malloc(sizeof(stack));
    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    s->length = 16;  // start with space for a few elements
    s->data = malloc(sizeof(int64_t) * s->length);
    if (s->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(s);
        return NULL;
    }
    s->top = -1;
    return s;
}

void deleteStack(stack** p_p_s) {
    free((*p_p_s)->data);
    (*p_p_s)->data = NULL;
    free((*p_p_s));
    (*p_p_s) = NULL;
}

result push(stack** p_p_s, int64_t item) {
    if ((*p_p_s)->top + 1 == (*p_p_s)->length) {
        // temp so that if realloc fails, the original data can still be freed
        int64_t* temp =
            realloc((*p_p_s)->data, (*p_p_s)->length * 2 * sizeof(int64_t));
        if (temp == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            deleteStack(p_p_s);
            return 1;
        }
        (*p_p_s)->data = temp;
        (*p_p_s)->length *= 2;
    }
    ++((*p_p_s)->top);
    (*p_p_s)->data[(*p_p_s)->top] = item;
}

int64_t pop(stack* p_s) {
    if (p_s->top < 0) {
        return -1;  // stack is array indices, so -1 is never valid
    }
    return p_s->data[(p_s->top)--];
}