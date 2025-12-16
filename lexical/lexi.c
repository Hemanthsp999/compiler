#include "lexi.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tokenizer *head = NULL;
// static char delimeter[] = " ";

void *insert_to_list(const char *value, char *type) {

        tokenizer *new_token = (tokenizer *)malloc(sizeof(tokenizer));
        if (!new_token) {
                fprintf(stderr,
                        "Error while allocating memory for 'new_token'\n");
                EXIT_FAILURE;
        }

        new_token->value = (char *)malloc(strlen(value) + 1);
        new_token->type = (char *)malloc(strlen(type) + 1);
        new_token->next = NULL;

        if (!new_token->value || !new_token->type) {
                fprintf(stderr, "Error in memory allocation\n");
                free(new_token->value);
                free(new_token->type);
                free(new_token);
        }

        strcpy(new_token->value, value);
        strcpy(new_token->type, type);
        new_token->next = NULL;

        if (head == NULL) {
                head = new_token;
        } else {
                tokenizer *curr = head;
                while (curr->next != NULL) {
                        curr = curr->next;
                }
                curr->next = new_token;
        }

        return new_token;
}

const char *keywords[] = {"int",    "if",    "else",    "float", "char",
                          "double", "while", "include", NULL};

const char *punctuators[] = {"}", "{", "]", "[", ")", "(", NULL};

void lexical_analyzer(const char *file_name) {

        printf("This is Lexical Analyzer section\n");
        FILE *file;
        file = fopen(file_name, "r");

        if (!file) {
                fprintf(stderr, "Error while opening the file\n");
                return;
        }

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
                for (int i = 0; buffer[i] != '\0'; i++) {

                        for (int j = 0; punctuators[j] != NULL; j++) {
                                if (strncmp(&buffer[i], punctuators[j],
                                            strlen(punctuators[j])) == 0) {
                                        printf("Found: %s\n", punctuators[j]);
                                }
                        }
                }
        }
        rewind(file);

        fclose(file);
        printToken();

        return;
}

void printToken() {

        tokenizer *p = head;
        while (p != NULL) {
                printf("Token -> ID: %s\t value: %s\n", p->type, p->value);
                p = p->next;
        }
}

void free_tokens() {
        tokenizer *curr = head;
        while (curr != NULL) {
                tokenizer *next = curr->next;
                free(curr->value);
                free(curr->type);
                free(curr);
                curr = next;
        }
        head = NULL;
}
