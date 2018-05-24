/** This file contains functions for formatting and printing output. **/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "roll.h"
#include "eval.h"
#include "output.h"

/* Verbosity setting */
int verbose;

/* The string to be next printed */
char *printstr;

/* The length of printstr */
int lenprintstr;

/* Turn verbose reporting on */
void setverbose() {
    printf("Verbose mode activated.\n");
    verbose = 1;
}

/* Turn verbose reporting off */
void setnoverbose() {
    printf("Verbose mode deactivated.\n");
    verbose = 0;
}

/* Reports if verbose mode is on or not */
void reportverbose() {
    queuemsg("Verbose mode is ");
    if (verbose) {
        queuemsg("on");
    } else {
        queuemsg("off");
    }

    queuemsg("\n");
    printmsg();
}

/* Appends str to the string to be printed */
void queuemsg(const char *str) {
    if (!lenprintstr) {
        lenprintstr = strlen(str);
        printstr = malloc(sizeof (str) * (1 + lenprintstr));
        strcpy(printstr, str);
    } else {
        lenprintstr += strlen(str);
        printstr = realloc(printstr, sizeof (char) * (1 + lenprintstr));
        strcat(printstr, str);
    }
}

/* Adds a number to the string to be printed */
void queuenum(int num) {
    char *str = malloc(sizeof (char) * (2 + (int) log10((double) num)));
    sprintf(str, "%d", num);
    queuemsg(str);
    free(str);
}

void printmsg() {
    printf("%s", printstr);
    if (lenprintstr) {
        free(printstr);
        lenprintstr = 0;
    }
}

/* Queues the values of all dice to print them to stdout */
void printdice(struct die *d) {
    if (!verbose) {
        return;
    }
 
    queuemsg("Rolled ");
    queuenum(d->num);
    queuemsg("d");
    queuenum(d->sides);
    queuemsg(": ");

    d = bottom(d);
    queuenum(d->val);
    d = d->next;

    while(d) {
        queuemsg("");
        queuemsg(", ");
        queuenum(d->val);
        d = d->next;
    };

    queuemsg("\n");
}
