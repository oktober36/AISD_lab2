#include "condition.h"


int condMaxLen(int N, Condition *c){
    int max, i;
    max = c->rcs[0].len;
    for (i = 1; i < N; i++){
        if (c->rcs[i].len > max)
            max = c->rcs[i].len;
    }
    return max;
}

void makeConditions(int N, Queue* qs, Condition *c, int currentTime){
    int i;
    if (c->time == -1)
        c->rcs = (RecCondition*)calloc(N, sizeof(RecCondition));
    c->time = currentTime;
    for (i = 0; i < N; i++){
        makeRecCondition(i, &(qs[i]), &(c->rcs[i]));
    }
}

void makeRecCondition(int recN, Queue* q, RecCondition *c){
    int strLen, j;
    char *buff;
    char *sep = " ";
    Node *tmp;
    strLen = queueLen(recN, q);
    buff = (char*)calloc(strLen + 1, sizeof(char));
    buff[0] = '#';
    sprintf(&(buff[1]), "%d", recN + 1);
    tmp = q->head;
    for (j = 0; j < q->n; j++){
        strcat(buff, sep);
        strcat(buff, tmp->value->id);
        tmp = tmp->next;
    }
    c->info = buff;
    c->len = strLen;
}
