#ifndef CONDITION_H_INCLUDED
#define CONDITION_H_INCLUDED

typedef struct RecCondition{
    char *info;
    int len;
} RecCondition;

typedef struct Condition{
    RecCondition *rcs;
    int time;
} Condition;

void makeRecCondition(int recN, Queue* q, RecCondition *c);
void makeConditions(int N, Queue* qs, Condition *c, int currentTime);
int condMaxLen(int N, Condition *c);

#endif // CONDITION_H_INCLUDED
