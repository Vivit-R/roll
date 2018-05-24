/** This file contains functions for making the rolls. **/
#include <stdlib.h>
#include <stdio.h>
#include "roll.h"
#include "settings.h"
#include "output.h"
#include "eval.h"


/* Recursively builds a double linked list of rolled dice. 
 * ALLOCATES ITS RETURN VALUES.
 * FIXME O(n) space */
struct die *rolldice(int dice, int sides) {
    if (dice <= 0 || sides <= 0) {
        return NULL;
    }

    struct die *ret = malloc(sizeof (struct die));

    ret->num = dice;
    ret->sides = sides;
    ret->val = rand() % sides + 1;
    ret->prev = NULL;
    ret->next = rolldice(dice - 1, sides);

    if (ret->next) {
        ret->next->prev = ret;
    }
    

    return ret;
}

/* Rerolls the die at d and returns a pointer to it. */
struct die *reroll(struct die *d) {
    if (!d)
        return NULL; /* Just in case */

    d->val = rand() % d->sides + 1;

    return d;
}


/* Frees all dice in a given pool of rolls */
void freedice(struct die *d) {
    d = bottom(d);
    struct die *freenext;

    while (d) {
        freenext = d->next;
        drop(d);
        d = freenext;
    }
}


struct die *explodedice(int dice, int sides) {
    struct die *d = rolldice(dice, sides);
    explode(d, dice);

    return d;
}


/* Standard additive roll */
int d(int dice, int sides) {
    struct die *rolls = rolldice(dice, sides);
    int ret = sumdice(rolls);
    printdice(rolls);

    if (verbose) {
        queuemsg("Total: ");
        queuenum(ret);
        queuemsg("\n");
    }

    freedice(rolls);
    return ret;
}

/* Exploding explosive roll */
int x(int dice, int sides) {
    struct die *rolls = explodedice(dice, sides);
    int ret = sumdice(rolls);
    if (verbose) {
        printdice(rolls);
    }
    freedice(rolls);
    return ret;
}
