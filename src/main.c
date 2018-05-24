#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "roll.h"
#include "roll.tab.h"
#include "eval.h"
#include "output.h"
#include "settings.h"

void init();
void cleanup();

extern int lenprintstr;

int main(int argc, char **argv) {
    printf("Welcome to roll interactive mode.\n> ");
    yyparse();

    cleanup();
    return 0;
}


void init() {
    srand(time(NULL));
    verbose = 1;
    lenprintstr = 0;
}

void cleanup() {
    if (lenprintstr) {
        free(printstr);
    }
}
