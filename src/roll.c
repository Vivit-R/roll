/** This file contains functions for making the rolls. **/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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


/* Wrapper function of rolling dice */
struct die *d(int dice, int sides) {
    struct die *rolls = rolldice(dice, sides);
    printdice(rolls);

    return rolls;
}

/* Playing cards, because Linsolv asked for it */
char *drawcard() {
    int suitnum = rand() % 4;
    int facenum = 1 + rand() % 13;

    char *ret = malloc(2 * sizeof (char));
    strcpy(ret, " ");

    switch (facenum) {
        case 1:
        default: /* <-- Can't happen */
            ret = forcestring(&ret, "Ace");
            break;

        case 2:
            ret = forcestring(&ret, "Deuce");
            break;

        case 3:
            ret = forcestring(&ret, "Trey");
            break;

        case 4:
            ret = forcestring(&ret, "Cater");
            break;

        case 5:
            ret = forcestring(&ret, "Cinque");
            break;

        case 6:
            ret = forcestring(&ret, "Sice");
            break;

        case 7:
            ret = forcestring(&ret, "Seven");
            break;

        case 8:
            ret = forcestring(&ret, "Eight");
            break;

        case 9:
            ret = forcestring(&ret, "Nine");
            break;

        case 10:
            ret = forcestring(&ret, "Ten");
            break;

        case 11:
            ret = forcestring(&ret, "Knave");
            break;

        case 12:
            ret = forcestring(&ret, "Queen");
            break;
        
        case 13:
            ret = forcestring(&ret, "King");
            break;

    }

    char *tmp = malloc(2 * sizeof (char));
    strcpy(tmp, " ");

    switch (suitnum) {
        case 0:
        default: /* <-- Can't happen */
            tmp = forcestring(&tmp, " of Spades");
            break;

        case 1:
            tmp = forcestring(&tmp, " of Clubs");
            break;

        case 2:
            tmp = forcestring(&tmp, " of Diamonds");
            break;
            
        case 3:
            tmp = forcestring(&tmp, " of Hearts");
            break;
    }

    ret = realloc(ret, sizeof (char) * (1 + strlen(ret) + strlen(tmp)));

    strcat(ret, tmp);

    free(tmp);

    return ret;    
}
