#ifndef __ROLL_EVAL__
#define __ROLL_EVAL__

#include "roll.h"

int cmp(const void *a, const void *b);
void drop(struct die *d);
struct die *dropdice(struct die *d, int drop);
// int sum(int *sumands, int nmembs);
int sumdice(struct die *d);
struct die *bottom(struct die *d); 

#endif
