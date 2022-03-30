#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

int input(int N, Queue* qs, Condition *cs, int csNum);
int step(int N, Queue* qs, Note *note, int *currentTime);
void clearDone(int N, Queue *qs);
void decreaseTS(int N, Queue* qs, int time);
int MinTS(int N, Queue* qs);
Queue* MinQueue(int N, Queue* qs);

#endif // TASK_H_INCLUDED
