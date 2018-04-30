#include <stdlib.h>
#include <stdio.h>
#include "eval.h"
#include "settings.h"

/* Drops the highest or lowest values of the array pointed to by rolls. */
/* Negative value for  drop  means drop high, positive value means drop low. */
int *drop(int **rolls, int numrolls, int drop) {
    if (drop == 0) {
        /* Nothing to do here */
        return *rolls;
    }

    /* We will sort this to find the highest and the lowest numbers */
    int *sorted = malloc(sizeof (int) * numrolls);
    int *ret = malloc(sizeof (int) * (numrolls - abs(drop)));

    for (int i = 0; i < numrolls; i++) {
        sorted[i] = (*rolls)[i];
    }

    /* qsort sorts the rolls in ascending order */
    qsort(sorted, numrolls, sizeof (int), cmp);

    if (drop > 0) {
        /* If drop is greater than zero, we will be dropping low -- or to look
           at it differently, keeping high.  We start at an index equal to
           drop, and then then iterate upward until we reach the end of the
           array, leaving out elements [0..drop] of the array. */
        for (int i = drop; i < numrolls; i++) {
            ret[i - drop] = sorted[i];
        }
    } else if (drop < 0) {
        /* If drop is less than zero, we will be dropping high -- or to look
           at it differently, keeping low.  This time we start at zero and
           iterate upward, with the ceiling of the array lowered by drop. */
        for (int i = 0; i < numrolls - drop; i++) {
            ret[i] = sorted[i];
        }
    } else {
        /* Can't happen: if drop is equal to zero,
           then we've already returned */
    }

    free(sorted);
    free(*rolls);

    /* Actually modify the rolls at the location they were called
     * FIXME: Do we really want to do this? */ 
    *rolls = ret;

    return *rolls;
}



/* For use with quicksort */
int cmp(const void *a, const void *b) {
    return *((int*) a) - *((int*) b);
}




/* Sums an array of integers */
int sum(int *sumands, int nmembs) {
    int ret = 0;
    for (int i = 0; i < nmembs; i++) {
        ret += sumands[i];
    }

    /* If verbose, print the sum.
       If noverbose, then reporting will be handled elsewhere. */
    if (verbose) {
        printf("Total: %d\n", ret);
    }

    return ret;
}
