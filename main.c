#include <stdio.h>
#include <stdlib.h>
#include "note.c"
#include "task.c"

int main()
{
    int i, msgLen;
    int qsSize = 20;
    int csNum = 20;
    Queue* qs;
    Condition *cs;
    int N;

    scanf("%d", &N);

    qs = (Queue*)calloc(N, sizeof(Queue));
    for (i = 0; i < N; i++){
        init(&(qs[i]));
    }

    cs = (Condition*)calloc(csNum, sizeof(Condition));
    for (i = 0; i < csNum; i++){
        cs[i].time = -1;
    }

    msgLen = input(N, qs, cs, csNum);

    if (msgLen == -1){
        printf("One of queues is full");
        return 0;
    }
    if (msgLen == -2){
        printf("Conditions more then predicted");
        return 0;
    }

    for (i = 0; i < N; i++){  // Очищаем память под очереди, т.к. они больше не нужны
        erase(&(qs[i]));
    }
    free(qs);
    qs = NULL;

    output(N, msgLen, cs);
}
