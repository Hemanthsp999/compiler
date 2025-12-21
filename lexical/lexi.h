#ifndef LEXI_
#define LEXI_
#include <stdbool.h>
#include <stdio.h>

typedef struct {
        char *store;
        int i;
} stack;

typedef struct tokens {
        char *value;
        char *type;
        struct tokens *next;
} tokenizer;

typedef struct {
        char *type;
        char *value;
        char *error_msg;
} Literals;

bool isKeyword(char *, int);
bool isOperator(char, char);
bool isPunctuator(char);
bool isIdentifier(char *, int);

void *insert_to_tokens(const char *, char *, tokenizer **);
void remove_white_space(char*);

void lexical_analyzer(const char *);
void init_validator(char *);
void printToken();
void free_tokens();

#endif
