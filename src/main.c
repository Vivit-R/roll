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
void finish();
void introduction();

extern int lenprintstr;

int main(int argc, char **argv) {
    init();

    introduction();
    yyparse();

    finish();
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

void finish() {
    printf("Goodbye. May your dice roll well.\n");
    cleanup();
    exit(0);
}

void introduction() {
    printf("Welcome to roll interactive mode.\n> ");
}
