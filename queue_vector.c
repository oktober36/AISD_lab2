#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void init(int N, Queue* q){
    int i;
    q->queue = (Note*)calloc(N, sizeof(Note));

    for (i = 0; i < N; i++)
        q->queue[i].ta = -1;

    q->N = N;
    q->n = 0;
    q->head = 0;
    q->tail = 0;
    q->totalTS = 0;
    q->currentTS = 0;
}

int push(Note a, Queue* q){
    if (q->n == q->N)
        return 0;
    if (q->n == 0)
        q->currentTS = a.ts;
    q->queue[q->tail] = a;
    q->tail = (q->tail + 1) % q->N;
    q->n++;
    q->totalTS += a.ts;
    return 1;
}

Note* pull(Queue* q){
    Note* out;
    if (q->n==0)
        return NULL;
    out = &(q->queue[q->head]);
    q->head = (q->head + 1) % q->N;
    q->n--;
    q->currentTS = q->queue[q->head].ts;
    q->totalTS -= out->ts;
    return out;
}

int queueLen(int qNum, Queue* q){
    int i;
    int len = 1; // №
    len += floor(log(qNum + 1)/log(10)) + 1; //Определяем кол-во чисел в номере
    if (q->n == 0)
        return len;
    for (i = 0; i < q->n; i++){
        len += 1 + strlen(q->queue[i].id);
    }
    return len;
}

void erase(Queue *q){
    int i;

    for (i = 0; q->queue[i].ta != -1; i++)
        free(q->queue[i].id);
    free(q->queue);
    q->queue = NULL;
    q->N = 0;
    q->n = 0;
    q->head = 0;
    q->tail = 0;
    q->totalTS = 0;
    q->currentTS = 0;
}
