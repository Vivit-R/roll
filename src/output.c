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

/* Are we ready to eport the final result of a given line of input? */

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
    char *str;
    if (num == 0) {
        str = malloc(sizeof (char) * 2);
    } else {
        str = malloc(sizeof (char) * (2 + (int) log10((double) num)));
    }

    sprintf(str, "%d", num);
    queuemsg(str);
    free(str);
}

/* Clears the message queue */
void flushmsg() {
    if (lenprintstr) {
        free(printstr);
        lenprintstr = 0;
    }
}

/* Prints message and flushes the queued messages */
void printmsg() {
    printf("%s", printstr);
    flushmsg();
}


/** Reporting functions to be called by the yacc file **/
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

/* Reports the numerical result of a roll or mathematical expression,
   with given prefix. */
int reportresult(const char *prefix, int result) {
    queuemsg("Result: ");
    queuenum(result);
    printmsg();
    return result;
}

/* Reports whether or not a check was successful */
void reportsuccess(int check) {
    queuemsg(check ? "Success." : "Failure.");
    printmsg();
}


/* Reports the result of an arithmetic evaluation */
void report_arithmetic(int a, char op, int b, int r) {
    if (!verbose) {
        return;
    }
    queuenum(a);
   
    /* Putting op into a string so it can be passed to queuemsg() */
    char *opstr = malloc(2 * sizeof (char));
    opstr[0] = op;
    opstr[1] = '\0';
    queuemsg(opstr);
    free(opstr);
    
    queuenum(b);
    queuemsg("=");
    queuenum(r);

    queuemsg("\n");
    printmsg();
}


/*** Misc. utility ***/

/* Makes room in the string at the pointer pointed to by dest and copies.
   the string into dest.
   Beware of dangling pointers!  Make sure you assign the value at dest to the
   return value of this function when calling this function. */
char *forcestring(char **dest, const char *newstring) {
    *dest = realloc(*dest, sizeof (char) * (1 + strlen(newstring)));
    strcpy(*dest, newstring);

    return *dest;
}
