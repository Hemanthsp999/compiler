#ifndef LEXI_
#define LEXI_
#include <stdio.h>
#include <stdbool.h>

typedef struct tokens {
        char *value;
        char *type;
        struct tokens *next;
} tokenizer;

tokenizer *parse_punctuators(char *);
tokenizer *insert_to_tokens(char*, char*, tokenizer **);
tokenizer *parse_operators(char *);
tokenizer *parse_keywords(char*);
char* isKeyword(char*);
bool isPunctuator(char*);
void lexical_analyzer(const char *);
void printToken();
void free_tokens();

#endif
