/**
 * @file stack.h
 * @brief Header file for stack data structure implementation.
 *
 * This file contains the declarations and documentation for the stack data
 * structure. The stack is used to track the positions of brackets in the
 * interpreter
 */

#ifndef BRAINF_STACK_H
#define BRAINF_STACK_H

#include <stdint.h>

typedef struct {
    int64_t* data;
    int64_t length, top;
} stack;

typedef enum { SUCCESS = 0, FAILURE = 1 } result;

/**
 * @brief Initialize a stack
 * @return A pointer to a stack
 */
stack* createStack();

/**
 * @brief Frees a pointer stack and its associated memory
 * @param p_p_s a pointer to the pointer to the stack
 */
void deleteStack(stack** p_p_s);

/**
 * @brief Adds an element to the stack. Exits on memory allocation failures
 * (after cleaning up)
 * @param p_p_s A pointer to a pointer to a stack
 * @param item The item to push
 * @return 1 if the push failed, 0 if it succeeded
 */
result push(stack** p_p_s, int64_t item);

/**
 * @brief Remove the top element from the stack (if it exists);
 * @param p_s A pointer to the stack
 * @return The element at the top of the stack, or -1 if it doesn't exist
 */
int64_t pop(stack* p_s);

#endif  // BRAINF_STACK_H