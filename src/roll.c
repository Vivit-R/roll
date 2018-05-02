/** This file contains functions for making the rolls. **/
#include <stdlib.h>
#include <stdio.h>
#include "roll.h"
#include "settings.h"
#include "eval.h"

int verbose;

/* Standard additive roll */
int d(int dice, int sides) {
    struct die *rolls = rolldice(dice, sides);
    struct die *trace = rolls;

    int ret = 0;

    while (trace) {
        ret += trace->val;
        trace = trace->next;
    }

    freedice(rolls);
    return ret;
}


/* Recursively builds a double linked list of rolled dice. 
 * ALLOCATES ITS RETURN VALUES.
 * FIXME O(n) space */
struct die *rolldice(int dice, int sides) {
    if (dice <= 0 || sides <= 0) {
        return NULL;
    }

    struct die *ret = malloc(sizeof (struct die));

    ret->val = rand() % sides + 1;
    ret->prev = NULL;
    ret->next = rolldice(dice - 1, sides);

    if (ret->next) {
        ret->next->prev = ret;
    }

    return ret;
}


/* Frees the dice in a given pool of rolls */
void freedice(struct die *d) {
    d = bottom(d);
    struct die *freenext;

    while (d) {
        freenext = d->next;
        drop(d);
        d = freenext;
    }
}
