#include "lexical/lexi.h"
#include <stdio.h>

int main(void) {

        printf("This is compiler project for fun!\n");
        char *file = "sample.unn";
        lexical_analyzer(file);
        free_tokens();
        return 0;
}
