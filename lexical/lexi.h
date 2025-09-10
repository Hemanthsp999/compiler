#ifndef LEXI_
#define LEXI_
#include <stdbool.h>
#include <stdio.h>

typedef struct tokens {
        char *value;
        char *type;
        struct tokens *next;
} tokenizer;

bool isKeyword(char *);
bool isOperators(char *);
bool isPunctuator(char *);
void *parse_punctuators(char *);
void *insert_to_tokens(char *, char *, tokenizer **);
void *parse_operators(char *);
void *parse_keywords(char *);
void lexical_analyzer(const char *);
void printToken();
void free_tokens();

#endif
