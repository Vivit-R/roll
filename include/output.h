#ifndef __OUTPUT__
#define __OUTPUT__

extern char *printstr;

void queuemsg(const char *str);
void flushmsg();
void printmsg();
void queuenum(int num);

void reportsuccess(int check);
void report_arithmetic(int a, char op, int b, int r);
int reportresult(const char *prefix, int result); 

char *forcestring(char **dest, const char *newstring);

#endif
