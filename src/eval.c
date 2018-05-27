#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "eval.h"
#include "output.h"
#include "settings.h"


/* Returns the bottom of the die pool in which the given die is contained. */
struct die *bottom(struct die *dee) {
    /* Iterate until at the bottom */
    while (dee && dee->prev) {
        dee = dee->prev;
    }
    return dee;
}

/* Returns the top of the die pool in which the given die is contained. */
struct die *top(struct die *dee) {
    /* Iterate until at the top */
    while (dee && dee->next) {
        dee = dee->next;
    }
    return dee;
}


/* Removes and frees a die from the pool. A standard linked-list deletion. */
void drop(struct die *dee) {
    if (dee->next) {
        dee->next->prev = dee->prev;
    }

    if (dee->prev) {
        dee->prev->next = dee->next;
    }

    free(dee);
}


/* Drops the highest or lowest values in the given die pool.
 * Negative value for dropn means drop high, positive means drop low. */
// FIXME: O(n^2) time
struct die *dropdice(struct die *dee, int dropn) {
    /*  lowest and prepare the
       memory location for the die we intend to drop */
    struct die *dropit = bottom(dee);

    while (dropn > 0) {
        dee = bottom(dee);
        dropit = dee;
        while (dee->next) {
            /* If the value of the die at dee is less than the value of the die
               at dropit, set dropit equal to dee. */
            if (dee->val < dropit->val) {
                dropit = dee;
            }
            dee = dee->next;
        }

        drop(dropit);
        dropn--;
    }

    /* Do the same, but dropping high instead of low. */
    while (dropn < 0) {
        dee = bottom(dee);
        dropit = dee;
        while (dee->next) {
            /* If the value of the die at dee is less than the value of the die
               at dropit, set dropit equal to dee. */
            if (dee->val > dropit->val) {
                dropit = dee;
            }
            dee = dee->next;
        }

        drop(dropit);
        dropn++;
    }

    return bottom(dee);
}


/* Checks for maximum value in a pool, rolls that many dice and adds the new
   ones to the pool. The "limiter" parameter is used to count how many times
   over the current pool has exploded, to make sure this does not exceed
   EXPLODE_LIMIT.

   TODO: Implement sophistocated conditional explosion. */
struct die *explode(struct die *dee, int limiter) {
    int explosions = 0;

    explosions = countsuccesses(dee, dee->sides, "=");

    if (explosions + limiter > EXPLODE_LIMIT) {
        explosions = EXPLODE_LIMIT - limiter;
    }

    if (explosions) {
        struct die *newdice = d(explosions, dee->sides);
        explode(newdice, limiter + explosions);
        joinpools(dee, newdice);
    }

    return dee;
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
int countsuccesses(struct die *dee, int tn, const char *test) {
    dee = bottom(dee);
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
    while (dee) {
        switch (op) {
            case 1: if (dee->val > tn) count++;
                break;
            case 2: if (dee->val < tn) count++;
                break;
            case 3: if (dee->val >= tn) count++;
                break;
            case 4: if (dee->val <= tn) count++;
                break;

            default: if (dee->val == tn) count++;
                break;
        }

        dee = dee->next;
    }

    return count;
}


/* Sums the value of the dice in the pool of which the die at the given pointer
 * is a member */
int sumdice(struct die *dee) {
    /* Iterate to the bottom of the linked list */
    while (dee->prev) {
        dee = dee->prev;
    }

    int sum = 0;

    /* Iterate upwards through the linked list until the end is reached */
    while (dee) {
        sum += dee->val;
        dee = dee->next;
    }

    if (verbose) {
        queuemsg("Total: ");
        queuenum(sum);
        queuemsg("\n");
    }

    return sum;
}

/* Sum the dice and free the pointer */
int destructive_sumdice(struct die *dee) {
    int ret = sumdice(dee);
    freedice(dee);
    return ret;
}

