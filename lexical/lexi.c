#include "lexi.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tokenizer *head = NULL;
const char *header[] = {"stdio", "stdbool"};
const char *keywords[] = {"int",    "if",    "else",    "float",  "char",
                          "double", "while", "include", "return", NULL};
const char *punctuators[] = {"}", "{", "]",  "[", ")",
                             "(", ";", "\"", ".", NULL};
const char *operators[] = {"=", "==", "++", "--", "+=", "*=", "/", "%", NULL};

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

bool isPunctuator(char c) {
        for (int i = 0; punctuators[i] != NULL; i++) {
                if (c == punctuators[i][0])
                        return true;
        }

        return false;
}

bool isOperator(char char_1, char char_2) {

        if (isPunctuator(char_1) || isPunctuator(char_2) || isalpha(char_1) ||
            isalpha(char_2))
                return false;

        for (int i = 0; operators[i] != NULL; i++) {

                if (char_1 == operators[i][0] && char_2 == operators[i][0])
                        return true;
                else if (char_1 == operators[i][0] || char_2 == operators[i][0])
                        return true;
        }
        return false;
}

bool isKeyword(char *word, int i) {
        if (keywords[i] == NULL) {
                return false;
        }

        if (strcmp(word, keywords[i]) == 0) {
                return true;
        }

        return isKeyword(word, i + 1);
}

bool isIdentifier(char *word, int i) {
        if (!isKeyword(word, i) || !isPunctuator(*word)) {
                return true;
        }

        return isIdentifier(word, i += 1);
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
        char word[50];
        int w = 0;
        while (fgets(buffer, sizeof(buffer), file) != NULL) {

                for (int i = 0; buffer[i] != '\0'; i++) {
                        char *temp_op1 = &buffer[i];
                        char *temp_op2 = &buffer[i + 1];

                        if (isalnum(buffer[i]) || buffer[i] == '_') {
                                word[w++] = buffer[i];
                        } else {
                                if (w > 0) {
                                        word[w] = '\0';

                                        if (isKeyword(word, 0))
                                                insert_to_list(word, "KEYWORD");
                                        else if (isIdentifier(word, 0)) {
                                                insert_to_list(word,
                                                               "IDENTIFIER");
                                        }
                                        w = 0;
                                }
                                if (isPunctuator(buffer[i])) {
                                        char temp[2];
                                        temp[0] = buffer[i];
                                        temp[1] = '\0';
                                        insert_to_list(temp, "PUNCTUATOR");

                                } else if (isOperator(*temp_op1, *temp_op2)) {
                                        char temp_op[3];
                                        temp_op[0] = *temp_op1;
                                        temp_op[1] = *temp_op2;
                                        temp_op[2] = '\0';
                                        insert_to_list(temp_op, "OPERATORS");
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
