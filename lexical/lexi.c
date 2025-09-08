#include "lexi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tokenizer *head = NULL;
static char delimeter[] = " ";

tokenizer *insert_to_list(char *value, char *type) {

        tokenizer *new_token = (tokenizer *)malloc(sizeof(tokenizer));
        if (!new_token)
                return new_token;

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

tokenizer *parse_keywords(char *current) {
        char *token;
        token = strtok(current, delimeter);

        while (token != NULL) {
                for (int i = 0; token[i] != '\0'; i++) {
                        if (strcmp(token, "int"))
                                printf("val %c", token[i]);
                }
                token = strtok(NULL, delimeter);
        }
        return NULL;
}

tokenizer *parse_operators(char *current) {

        if (*current == '+' || *current == '-' || *current == '/' ||
            *current == '*') {
                char temp_val[2];
                temp_val[0] = *current;
                temp_val[1] = '\0';
                char *type = "Separator";
                return insert_to_list(temp_val, type);
        }

        return NULL;
}

/* Some bugs are here. */
tokenizer *parse_punctuators(char *current) {

        char *token;
        token = strtok(current, delimeter);

        while (token != NULL) {
                for (int i = 0; token[i] != '\0'; i++) {
                        if (token[i] == '{' || token[i] == '}' ||
                            token[i] == '(' || token[i] == ')' ||
                            token[i] == ',' || token[i] == '.' ||
                            token[i] == ';' || token[i] == ':') {
                                char temp_val[2];
                                temp_val[0] = token[i];
                                temp_val[1] = '\0';
                                insert_to_list(temp_val, "Separator");
                        }
                }
                token = strtok(NULL, delimeter);
        }
        return NULL;
}

void printToken() {
        tokenizer *p = head;
        while (p->next != NULL) {
                printf("Type: %s\tValue: %s\n", p->type, p->value);
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
                if (*buffer == '\t' || *buffer == '\n' || *buffer == '\0') {
                        continue;
                }
                // parse_punctuators(buffer);
                parse_keywords(buffer);
        }

        fclose(file);
        printToken();
}
