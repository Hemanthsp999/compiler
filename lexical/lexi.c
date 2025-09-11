#include "lexi.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tokenizer *head = NULL;
static char delimeter[] = " ";

const char *keyword_dict[] = {
    "int",  "continue", "if",       "else", "return", "void",
    "char", "float",    "double",   "void", "short",  "_Bool",
    "long", "signed",   "unsigned", "bool", NULL};

const char *operators_dict[] = {"+",  "-",  "*",  "/",  "%",  "=",  "&&",
                                "||", "!",  "&",  "|",  "^",  "~",  "++",
                                "--", "==", "!=", "/=", "+=", "-=", "*=",
                                "%=", ">",  "<",  ">=", "<=", NULL};

const char *punc_dict[] = {"}", "{", ")", "(", "]", "[",
                           "?", ":", ";", ",", NULL};

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

bool isKeyword(const char *word) {

        for (int i = 0; keyword_dict[i] != NULL; i++) {
                if (strcmp(word, keyword_dict[i]) == 0)
                        return true;
        }

        return false;
}

void *parse_keywords(char *inputLine) {

        char buffer[100];
        uint j = 0;

        int inputLen = strlen(inputLine);
        for (int i = 0; i <= inputLen; i++) {
                char word = inputLine[i];

                if (isalnum(word) || word == '_') {
                        if (j < sizeof(buffer) - 1) {
                                buffer[j++] = word;
                        }
                } else {
                        if (j > 0) {
                                buffer[j] = '\0';
                                if (isKeyword(buffer))
                                        insert_to_list(buffer, "KEYWORD");
                                j = 0;
                        }
                }
        }
        return 0;
}

bool isOperators(const char *word) {

        for (int i = 0; operators_dict[i] != NULL; i++) {
                if (strcmp(word, operators_dict[i]) == 0)
                        return true;
        }

        return false;
}

void *parse_operators(char *input_line) {

        char buffer[3] = {0};
        int len = strlen(input_line);
        for (int i = 0; i < len; i++) {
                buffer[0] = input_line[i];
                buffer[1] = input_line[i + 1];
                buffer[2] = '\0';

                if (isOperators(buffer)) {
                        insert_to_list(buffer, "OPERATOR");
                        i++;
                        continue;
                }

                buffer[1] = '\0';
                if (isOperators(buffer)) {
                        insert_to_list(buffer, "OPERATOR");
                        continue;
                }
        }

        return 0;
}

void *parse_identifiers(char *input_line) {

        char *token = strtok(input_line, delimeter);
        while (token != NULL) {
                if (!parse_keywords(token) || !parse_punctuators(token) ||
                    !parse_operators(token)) {
                        printf("val: %s\n", token);
                }

                token = strtok(NULL, delimeter);
        }

        return 0;
}

bool isPunctuator(const char *word) {

        for (int i = 0; punc_dict[i] != NULL; i++) {
                if (strcmp(word, punc_dict[i]) == 0)
                        return true;
        }
        return false;
}

void *parse_punctuators(char *input_line) {

        char buffer[3];
        int len = strlen(input_line);

        for (int i = 0; i <= len; i++) {
                buffer[0] = input_line[i];
                buffer[1] = input_line[i + 1];
                buffer[2] = '\0';

                if (isPunctuator(buffer)) {
                        insert_to_list(buffer, "PUNCTUATOR");
                        i++;
                        continue;
                }

                buffer[1] = '\0';
                if (isPunctuator(buffer)) {
                        insert_to_list(buffer, "PUNCTUATOR");
                }
        }
        return 0;
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
                // parse_keywords(buffer);
                // parse_operators(buffer);
                // parse_punctuators(buffer);
                parse_identifiers(buffer);
        }
        rewind(file);

        fclose(file);
        // printToken();
}

void printToken() {

        tokenizer *p = head;
        while (p != NULL) {
                printf("Token -> ID: %s\tvalue: %s\n", p->type, p->value);
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
