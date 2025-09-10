#include "lexi.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tokenizer *head = NULL;
static char delimeter[] = " ";

void *insert_to_list(char *value, char *type) {

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

bool isKeyword(char *word) {
        const char *keyword_dict[] = {"int",      "if",    "else",  "return",
                                      "void",     "char",  "float", "double",
                                      "void",     "short", "long",  "signed",
                                      "unsigned", "bool",  NULL};
        bool iskeywords = false;

        for (int i = 0; keyword_dict[i] != NULL; i++) {
                if (strcmp(word, keyword_dict[i]) == 0) {
                        iskeywords = true;
                        // printf("val: %s\t", word);
                        insert_to_list(word, "KEYWORD");
                }
        }

        return iskeywords;
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
                                if (!isKeyword(buffer))
                                        continue;
                                j = 0;
                        }
                }
        }
        return 0;
}

bool isOperators(char *word) {

        const char *operators_dict[] = {
            "+",  "-",  "*",  "/",  "%",  "=",  "&&", "||", "!",
            "&",  "|",  "^",  "~",  "++", "--", "==", "!=", "/=",
            "+=", "-=", "*=", "%=", ">",  "<",  ">=", "<=", NULL};

        for (int i = 0; operators_dict[i] != NULL; i++) {
                if (strcmp(word, operators_dict[i]) == 0) {
                        insert_to_list(word, "OPERATOR");
                        return true;
                }
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
                        printf("Operator found: %s\n", buffer);
                        i++;
                        continue;
                }

                buffer[1] = '\0';
                if (isOperators(buffer))
                        printf("Operator found: %s\n", buffer);
        }

        return 0;
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

void *parse_punctuators(char *input_line) {

        char *token;
        token = strtok(input_line, delimeter);

        while (token != NULL) {
                bool ispunc = isPunctuator(token);
                if (!ispunc)
                        goto NextToken;

        NextToken:
                token = strtok(NULL, delimeter);
        }

        return 0;
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
                //parse_keywords(buffer);
                //parse_punctuators(buffer);
                parse_operators(buffer);
        }

        fclose(file);
        printToken();
}
