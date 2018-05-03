#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "roll.h"
#include "roll.tab.h"
#include "eval.h"


int main(int argc, char **argv) {
    struct die *roll1 = rolldice(3, 6);

    srand(time(NULL));

    printf("3d6: ");
    printdice(roll1);

    struct die *roll2 = rolldice(4, 6);

    printf("4d6: ");
    printdice(roll2);

    roll2 = dropdice(roll2, 1);
    
    printf("The above, with low dropped: ");

    printdice(roll2);


    struct die *roll3 = explodedice(5, 6);

    printf("5x6: ");

    printdice(roll3);

    freedice(roll1);
    freedice(roll2);
    freedice(roll3);

    printf("Welcome to roll interactive mode.\n> ");
    yyparse();

    return 0;
}

