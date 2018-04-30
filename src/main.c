#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "roll.h"
#include "eval.h"

/*
int main(int argc, char **argv) {
    srand(time(NULL));
    int *roll1 = malloc(3 * sizeof (int));
    int *roll2 = malloc(4 * sizeof (int));
    rolldice(roll1, 3, 6);
    rolldice(roll2, 4, 6);


    printf("3d6: %d, %d, %d\n", roll1[0], roll1[1], roll1[2]); 
    printf("4d6: %d, %d, %d, %d\n", roll2[0], roll2[1], roll2[2], roll2[3]);
    drop(&roll2, 4, 1);
    printf("The above, with low dropped:  %d, %d, %d\n", roll2[0], roll2[1], roll2[2]);

    free(roll1);
    free(roll2);

    return 0;
} */
