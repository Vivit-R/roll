#include <stdlib.h>
#include <stdio.h>
#include "eval.h"
#include "settings.h"


/* Returns the bottom of the die pool in which the given die is contained. */
struct die *bottom(struct die *d) {
    while (d && d->prev) {
        d = d->prev;
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
