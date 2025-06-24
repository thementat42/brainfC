/**
 * @file brainf.c
 * The main brainf*** interpreter
 * Build using CMake, or just
 * gcc stack.c brainf.c -o brainf
 * clang stack.c brainf.c -o brainf
 * cl stack.c brainf.c -o brainf
 */

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define TAPE_LENGTH 30000
#define MAX_PROGRAM_SIZE 100000

uint8_t tape[TAPE_LENGTH];

/**
 * @brief Initialize the tape to be all zeros
 */
void initializeTape() {
    for (size_t i = 0; i < TAPE_LENGTH; ++i) {
        tape[i] = 0;
    }
}

/**
 * @brief Preprocesses the program to check if all square brackets are matched
 * @param program The script to check
 * @return SUCCESS if all brackets are matched, FAILURE otherwise
 */
result areBracketsValid(const char* program) {
    int64_t depth = 0;
    while (*program) {
        if (*program == '[') {
            depth++;
        } else if (*program == ']') {
            depth--;
        }
        ++program;
    }
    return depth == 0 ? SUCCESS : FAILURE;
}

/**
 * @brief Runs the code
 * @param program The brainf*** script
 * @return SUCCESS if the program ran successfully, FAILURE if there was an error
 */
result interpret(const char* program) {
    if (!areBracketsValid(program)) {
        fprintf(stderr, "Error: Mismatched number of brackets");
        return FAILURE;
    }
    initializeTape();  // clear the tape
    const char* p = program;
    size_t pointer = 0;
    stack* s = createStack();

    result res = SUCCESS;

    while (1) {
        switch (*p) {
            case '>':
                pointer = (pointer + 1) % TAPE_LENGTH;
                break;
            case '<':
                pointer = (pointer - 1 + TAPE_LENGTH) % TAPE_LENGTH;
                break;
            case '+':
                ++tape[pointer];
                break;
            case '-':
                --tape[pointer];
                break;
            case '.':
                printf("%c", tape[pointer]);
                break;
            case ',':
                char c;
                if (scanf("%c", &c) != 1) {
                    fprintf(stderr, "Error: Failed to read input\n");
                    res = FAILURE;
                    goto cleanup;
                }
                tape[pointer] = (uint8_t)c;
                break;
            case '[':
                if (tape[pointer]) {
                    if (push(&s, p - program) == FAILURE) {
                        res = FAILURE;
                        goto cleanup;
                    }
                    break;
                }
                int64_t nestDepth = 0;
                while (1) {
                    ++p;
                    if (*p == '\0') {
                        goto cleanup;
                    }
                    if (*p == '[') {
                        ++nestDepth;
                    } else if (*p == ']') {
                        if (nestDepth) {
                            nestDepth--;
                        } else {
                            break;
                        }
                    }
                }
                break;
            case ']':
                p = program + pop(s) - 1;
                break;
            case '\0':
                goto cleanup;
            default:
                break;  // All other characters are comments
        }
        ++p;
    }
cleanup:
    deleteStack(&s);

    return res;
}

/**
 * @brief Reads a file into a buffer
 * @param filename The name of the file to read
 * @param buffer The buffer to read into
 * @return SUCCESS if the file was read successfully, FAILURE otherwise
 */
result readFile(const char* filename, char* buffer) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return FAILURE;
    }
    
    size_t bytesRead = fread(buffer, sizeof(char), MAX_PROGRAM_SIZE - 1, file);
    if (bytesRead == 0 && ferror(file)) {
        fprintf(stderr, "Error: Could not read from file %s\n", filename);
        fclose(file);
        return FAILURE;
    }
    if (bytesRead == MAX_PROGRAM_SIZE - 1) {
        fprintf(stderr, "Warning: File %s is too large, truncating\n", filename);
    }
    buffer[bytesRead] = '\0';
    
    fclose(file);
    return SUCCESS;
}

int main(int argc, char const* argv[]) {
    if (argc <= 1) {
        // No code passed in, default to hello world
        const char* program =
            "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++.."
            "+++."
            ">>.<-.<.+++.------.--------.>>+.>++.";  // Hello world!
        result res = interpret(program);
        return res == SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    
    for (size_t i = 1; i < argc; ++i) {
        // Check if the argument is a file
        if (strstr(argv[i], ".bf") || strstr(argv[i], ".b") || strstr(argv[i], ".brainfuck")) {
            char buffer[MAX_PROGRAM_SIZE];
            if (readFile(argv[i], buffer) == FAILURE) {
                return EXIT_FAILURE;
            }
            result res = interpret(buffer);
            if (res == FAILURE) {
                return EXIT_FAILURE;
            }
        } else {
            // Treat as direct code
            result res = interpret(argv[i]);
            if (res == FAILURE) {
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}
