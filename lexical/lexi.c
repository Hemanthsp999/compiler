#include "lexi.h"
#include <stdio.h>
#include <string.h>
//

tokenizer parse_operators(char current) {
        tokenizer token = {
            0,
        };

        switch (current) {
        case '+':
                token.token_value = &current;
                token.type.operator_handler.AirthmeticOperator = ADDITION;
                printf("token value: %c\t token type: %d", *token.token_value,
                       token.type.operator_handler.AirthmeticOperator);
                break;
        case '=':
                token.token_value = &current;
                token.type.separator_operator = EQUAL;
                printf("token value: %c\t token type: %d", *token.token_value,
                       token.type.separator_operator);
                break;
        case '*':
                token.token_value = &current;
                token.type.operator_handler.AirthmeticOperator = MULTIPLY;
                printf("token value: %c\t token type: %d", *token.token_value,
                       token.type.operator_handler.AirthmeticOperator);
                break;
        case '/':
                token.token_value = &current;
                token.type.operator_handler.AirthmeticOperator = DIVIDE;
                printf("token value: %c\t token type: %d", *token.token_value,
                       token.type.operator_handler.AirthmeticOperator);
                break;
        default:
                token.token_value = 0;
                token.type.error_msg = "Invalid operator";
        }

        return token;
}

/* Some bugs are here. */
tokenizer parse_identifiers(char current) {
        tokenizer token = {
            0,
        };

        char *data_type = "int";
        char *start = strchr(&current, ' ');
        if (start) {
                while (*start == *data_type || *start == ' ')
                        start++;

                char *end = start;
                while (*end != ';' && *end != ' ' && *end != '\t' &&
                       *end != '\0')
                        end++;
                int len = end - start;
                char identifier[len + 1];
                strncpy(identifier, start, len);
                printf("Debug: %s\n", identifier);
                printf("Debug End: %s\n", end);
        }

        // printf("Value: %s", start);
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
                // printf("%c\n", current);
                parse_operators(current);
                // parse_identifiers(current);
                current = fgetc(file);
        }

        fclose(file);
}
