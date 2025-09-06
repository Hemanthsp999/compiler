#include "lexi.h"
#include <stdio.h>
#include <string.h>
//

tokenizer parse_operators(char current) {
        tokenizer token = {0, 0};

        if (strcmp(&current, "+") == 0) {
                token.type = OPERATORS;
                token.token_value = "+";
        } else {
                return token;
        };

        return token;
}

void lexical_analyzer(const char *file_name) {
        printf("This is Lexical Analyzer section\n");
        FILE *file;
        file = fopen(file_name, "r");

        if (!file) {
                fprintf(stderr, "Error while opening the file\n");
                return;
        }

        printf("File contents\n");
        // char buffer[1024];
        char current = fgetc(file);
        while (current != EOF) {
                printf("%c\n", current);
                tokenizer token = parse_operators(current);
                printf("token type: %d, token_value: %s\n", token.type,
                       token.token_value);
                current = fgetc(file);
        }

        fclose(file);
}
