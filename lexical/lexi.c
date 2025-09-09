#include "lexi.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tokenizer *head = NULL;
static char delimeter[] = " ";

tokenizer *insert_to_list(char *value, char *type) {

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

char *isKeyword(char *current) {
        const char *keyword_dict[] = {"if",     "int",   "switch", "for",
                                      "else",   "while", "do",     "return",
                                      "exit",   "main",  "void",   "float",
                                      "double", "char",  "bool",   "_Bool"};
        int dict_size = sizeof(keyword_dict) / sizeof(keyword_dict[0]);
        // printf("Source: %s\n", current);

        for (int i = 0; i < dict_size; i++) {

                if (strcmp(current, keyword_dict[i]) == 0) {
                        char *value = (char *)malloc(strlen(current) + 1);
                        strcpy(value, keyword_dict[i]);
                        return value;
                }
        }

        char *value = malloc(5);
        strcpy(value, "null");
        return value;
}

tokenizer *parse_keywords(char *current) {
        char *token;
        token = strtok(current, delimeter);

        while (token != NULL) {
                char *getKeywords = isKeyword(token);
                if (!getKeywords) {
                        free(getKeywords);
                        getKeywords = NULL;
                        goto nextLine;
                }

                char *temp_val = getKeywords;
                // printf("Debug: Parse %s\t Source: %s\n", temp_val, token);
                if (strcmp(temp_val, "null") == 0)
                        temp_val = NULL;

                if (temp_val != NULL)
                        insert_to_list(temp_val, "KEYWORD");

                free(getKeywords);

        nextLine:
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
                char *type = "OPERATOR";
                return insert_to_list(temp_val, type);
        }

        return NULL;
}

bool isPunctuator(char *current) {

        bool is_punc = false;
        for (int i = 0; current[i] != '\0'; i++) {
                if (current[i] == ')' || current[i] == '(' ||
                    current[i] == '}' || current[i] == '{' ||
                    current[i] == ';' || current[i] == ':' ||
                    current[i] == '?' || current[i] == ',') {
                        is_punc = true;
                        char punc = current[i];
                        // printf("found val: %c\t", *punctuator);
                        insert_to_list(&punc, "SEPARATOR");
                }
        }

        return is_punc;
}

tokenizer *parse_punctuators(char *current) {

        char *token;
        token = strtok(current, delimeter);

        while (token != NULL) {
                bool ispunc = isPunctuator(token);
                // printf("is punc: %d\n", ispunc);
                if (!ispunc)
                        goto goNext;

        goNext:
                token = strtok(NULL, delimeter);
        }
        return NULL;
}

void printToken() {

        tokenizer *p = head;
        while (p != NULL) {
                printf("Token -> type: %s\tvalue: %s\n", p->type, p->value);
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
                parse_punctuators(buffer);

                parse_keywords(buffer);
        }

        fclose(file);
        printToken();
}
