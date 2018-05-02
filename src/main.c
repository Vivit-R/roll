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

    struct die *printdie = roll1;
    while(printdie) {
        printf("%d", printdie->val);
        printdie = printdie->next;
        if (printdie) {
            printf(", ");
        }
    }

    printf("\n");

    struct die *roll2 = rolldice(4, 6);

    printf("4d6: %d, %d, %d, %d\n", roll2->val, roll2->next->val,
            roll2->next->next->val, roll2->next->next->next->val);

    roll2 = dropdice(roll2, 1);
    
    printf("The above, with low dropped:  %d, %d, %d\n", roll2->val,
            roll2->next->val, roll2->next->next->val);

    freedice(roll1);
    freedice(roll2);

//    yyparse();

    return 0;
}
