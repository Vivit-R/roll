#ifndef __OUTPUT__
#define __OUTPUT__

extern char *printstr;

void queuemsg(const char *str);
void flushmsg();
void printmsg();
void queuenum(int num);

void reportsuccess(int check);
int reportresult(const char *prefix, int result); 

char *forcestring(char **dest, const char *newstring);

#endif
