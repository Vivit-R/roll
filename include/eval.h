#ifndef __ROLL_EVAL__
#define __ROLL_EVAL__

#include "roll.h"

int cmp(const void *a, const void *b);
void drop(struct die *d);
struct die *dropdice(struct die *d, int drop);
int sumdice(struct die *d);
int destructive_sumdice(struct die *d);
int countsuccesses(struct die *d, int tn, const char *test);
struct die *bottom(struct die *d); 
struct die *explode(struct die *d, int limiter);
struct die *joinpools(struct die *d1, struct die *d2); 
void printdice(struct die *d);

/* The maximum number of dice that can be exploded. No exploding roll will
 * produce a pool with a number of results greater than EXPLODE_LIMIT. */
#define EXPLODE_LIMIT 32

#define GREATER 0
#define LESS    1
#define GREQUAL 2
#define LEQUAL  3

#endif
