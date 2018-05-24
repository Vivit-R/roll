#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "eval.h"
#include "settings.h"


/* Returns the bottom of the die pool in which the given die is contained. */
struct die *bottom(struct die *d) {
    while (d && d->prev) {
        d = d->prev;
    }
    return d;
}

/* Returns the top of the die pool in which the given die is contained. */
struct die *top(struct die *d) {
    while (d && d->next) {
        d = d->next;
    }
    return d;
}


/* Removes and frees a die from the pool. */
void drop(struct die *d) {
    if (d->next) {
        d->next->prev = d->prev;
    }

    if (d->prev) {
        d->prev->next = d->next;
    }

    free(d);
}


/* Drops the highest or lowest values in the given die pool.
 * Negative value for dropn means drop high, positive means drop low. */
// FIXME: O(n^2) time
struct die *dropdice(struct die *d, int dropn) {
    /*  lowest and prepare the
       memory location for the die we intend to drop */
    struct die *dropit = bottom(d);

    while (dropn > 0) {
        d = bottom(d);
        dropit = d;
        while (d->next) {
            /* If the value of the die at d is less than the value of the die
               at dropit, set dropit equal to d. */
            if (d->val < dropit->val) {
                dropit = d;
            }
            d = d->next;
        }

        drop(dropit);
        dropn--;
    }

    /* Do the same, but dropping high instead of low. */
    while (dropn < 0) {
        d = bottom(d);
        dropit = d;
        while (d->next) {
            /* If the value of the die at d is less than the value of the die
               at dropit, set dropit equal to d. */
            if (d->val > dropit->val) {
                dropit = d;
            }
            d = d->next;
        }

        drop(dropit);
        dropn++;
    }

    return bottom(d);
}


/* Checks for maximum value in a pool, rolls that many dice and adds the new
   ones to the pool. TODO: Implement complex conditional explosion. */
struct die *explode(struct die *d, int limiter) {
    int explosions = 0;

    explosions = countsuccesses(d, d->sides, "=");

    if (explosions + limiter > EXPLODE_LIMIT) {
        explosions = EXPLODE_LIMIT - limiter;
    }

    if (explosions) {
        struct die *newdice = rolldice(explosions, d->sides);
        explode(newdice, limiter + explosions);
        joinpools(d, newdice);
    }

    return d;
}


/* Combines two pools of dice together */
struct die *joinpools(struct die *d1, struct die *d2) {
    struct die *d1top = top(d1);
    struct die *d2bot = bottom(d2);

    /* Sanity check */
    if (!d2) {
        return d1;
    } else if (!d1) {
        return d2;
    }

    d1top->next = d2bot;
    d2bot->prev = d1top;

    return d1top;
}


/* Counts dice that fulfill a certain test given by a number and a string.
 * If the string is not recognized, default to "=". */
int countsuccesses(struct die *d, int tn, const char *test) {
    d = bottom(d);
    int op = 0;

    if (!strcmp(test, ">")) {
        op = 1;
    } else if (!strcmp(test, "<")) {
        op = 2;
    } else if (!strcmp(test, ">=")) {
        op = 3;
    } else if (!strcmp(test, "<=")) {
        op = 4;
    }

    int count = 0;
    while (d) {
        switch (op) {
            case 1: if (d->val > tn) count++;
                break;
            case 2: if (d->val < tn) count++;
                break;
            case 3: if (d->val >= tn) count++;
                break;
            case 4: if (d->val <= tn) count++;
                break;

            default: if (d->val == tn) count++;
                break;
        }

        d = d->next;
    }

    return count;
}


/* Sums the value of the dice in the pool of which the die at the given pointer
 * is a member */
int sumdice(struct die *d) {
    /* Iterate to the bottom of the linked list */
    while (d->prev) {
        d = d->prev;
    }

    int sum = 0;

    /* Iterate upwards through the linked list until the end is reached */
    while (d) {
        sum += d->val;
        d = d->next;
    }

    return sum;
}

