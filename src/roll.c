/** This file contains functions for making the rolls. **/
#include <stdlib.h>
#include <stdio.h>
#include "roll.h"
#include "settings.h"
#include "eval.h"

int verbose;
int splosions; /* FIXME: Ugly, ugly kludge */

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
 * then returns arr. Make sure enough space is allocated to hold this data! */
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

/* Exploding dice! */
int *explode(int *arr, int dice, int sides) {
    splosions = 0;
    int origdice = dice;

    for (int i = 0; i <= dice; i++) {
        arr[i] = 1 + rand() % sides;

        if (arr[i] == sides) {
            arr = realloc(arr, (++dice) * sizeof (int));
            splosions++;
        }
    }

    if (verbose) {
        printf("You rolled %d %d-sided exploding di%se: ", 
                origdice, sides, origdice != 1 ? "c" : "");

        for (int i = 0; i <= dice; i++) {
            printf("%d%s", arr[i], i == dice - 1 ? "\n" : ", ");
        }
    }
    
    return arr;
}

int x(int dice, int sides) {
    int *rolls = malloc(sizeof (int) * dice);
    explode(rolls, dice, sides);
    int ret = sum(rolls, dice+splosions); 
    if (!verbose) {
        printf("%d\n", ret);
    }
}
