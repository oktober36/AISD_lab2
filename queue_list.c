#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int push(Note a, Queue* q){
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL)
        return 0;
    tmp->value = (Note*) malloc(sizeof(Note));
    *(tmp->value) = a;
    if (q->n == 0){
        q->head = tmp;
        q->tail = tmp;
        q->currentTS = a.ts;
    }
    else {
        q->tail->next = tmp;
        q->tail = tmp;
    }
    q->n ++;
    q->totalTS += a.ts;
    return 1;
}

Note* pull(Queue* q){
    Node* out;
    if (q->n==0)
        return NULL;
    out = q->head;
    q->head = q->head->next;
    out->next = NULL;
    q->n--;
    if (q->n==0){
        q->tail = NULL;
        q->currentTS = 0;
        q->totalTS = 0;
    } else {
        q->currentTS = q->head->value->ts;
        q->totalTS -= out->value->ts;
    }
    return out->value;
}

int queueLen(int qNum, Queue* q){
    int i;
    int len = 1; // №
    Node* tmp = q->head;
    len += floor(log(qNum + 1)/log(10)) + 1; //Определяем кол-во чисел в номере
    for (i = 0; i < q->n; i++){
        len += 1 + strlen(tmp->value->id);
        tmp = tmp->next;
    }
    return len;
}

void init(Queue *q){
    q->head = NULL;
    q->tail = NULL;
    q->n = 0;
    q->currentTS = 0;
    q->totalTS = 0;
}

void erase(Queue *q){
    int i;
    Node *next, *cur;

    cur = q->head;
    for (i = 0; i < q->n; i++){
        next = cur->next;
        cur->next = NULL;
        free(cur->value);
        cur = next;
    }
    q->n = 0;
    q->head = NULL;
    q->tail = NULL;
    q->totalTS = 0;
    q->currentTS = 0;
}
