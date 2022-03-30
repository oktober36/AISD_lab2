#include "note.h"
#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED


typedef struct Node{
    Note* value;
    struct Node* next;
} Node;

typedef struct Queue{
    int n;
    Node *head;
    Node *tail;
    int totalTS;
    int currentTS;
} Queue;

Note* pull(Queue *q);
int push(Note a, Queue *q);
int queueLen(int qNum, Queue* q);
void erase(Queue *q);

#endif


/*
typedef struct Queue{
    int n;
    int N;
    int head;
    int tail;
    Note* queue;
    int totalTS;
    int currentTS;
} Queue;

Note* pull(Queue *q);
void init(int N, Queue *q);
int push(Note a, Queue *q);
int queueLen(int qNum, Queue* q);
void erase(Queue *q);
*/
