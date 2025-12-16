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

bool isKeyword(const char *);
bool isOperators(const char *);
bool isPunctuator(const char *);
bool isIdentifier(const char *);

void *parse_punctuators(char *);
void *insert_to_tokens(const char *, char *, tokenizer **);
void *parse_operators(char *);
void *parse_keywords(char *);
void *parse_identifiers(char *);
Literals *recursive_literal_extractor(const char *, int);
void *parse_literals(char *);

void lexical_analyzer(const char *);
void init_validator(char *);
void printToken();
void free_tokens();

#endif
