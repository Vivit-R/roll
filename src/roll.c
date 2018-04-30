/** This file contains functions for making the rolls. **/
#include <stdlib.h>
#include <stdio.h>
#include "roll.h"
#include "settings.h"
#include "eval.h"

int verbose;

/* Standard additive roll */
int d(int dice, int sides) {
    int *rolls = malloc(sizeof (int) * dice);
    rolldice(rolls, dice, sides);
    int ret = sum(rolls, dice);
    free(rolls);

    if (!verbose) {
        printf("%d\n", ret);
    }

    return ret;
}

/* Rolls dice and stores the results of each in the array pointed to by  arr,
 * then returns  arr . Make sure enough space is allocated to hold this data! */
int *rolldice(int *arr, int dice, int sides) {
    if (dice > 0 && sides > 0) {
        for (int i = 0; i < dice; i++) {
            arr[i] = 1 + rand() % sides;
        }
    }

    if (verbose) {
        printf("You rolled %d %d-sided di%se: ", dice, sides, 
                dice == 1 ? "" : "c" );
        for (int i = 0; i < dice; i++) {
            printf("%d%s", arr[i], i == dice - 1 ? "\n" : ", ");
        }
    }

    return arr;
}
