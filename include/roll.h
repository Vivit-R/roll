#ifndef __ROLL__
#define __ROLL__


/* One segment of a linked list for the lists of rolls */
struct die;
struct die {
    int val;
    struct die *next;
    struct die *prev;
};

struct die *rolldice(int dice, int sides);
int d(int dice, int sides);

struct die *explodedice(int dice, int sides);
int x(int dice, int sides);

void freedice(struct die *dietofree);

void setverbose();
void setnoverbose();

#endif
