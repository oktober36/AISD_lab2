#include "queue_list.c"
#include "condition_list.c"
#include "task.h"
#include <math.h>
#include <string.h>

void output(int N, int msgLen, Condition *cs){
    int *maxLens;
    int i, j;

    maxLens = (int*)calloc(msgLen, sizeof(int));
    for (i = 0; i < msgLen; i++){
        maxLens[i] = condMaxLen(N ,&(cs[i]));
        printf("%-*d", maxLens[i] + 1, cs[i].time);
    }
    for (j = 0; j < N; j++){
        putchar('\n');
        for (i = 0; i < msgLen; i++){
            printf("%-*s ", maxLens[i] ,cs[i].rcs[j].info);
        }
    }
}

int input(int N, Queue* qs, Condition *cs, int csNum){
    Note note;
    int i, j;
    int moment = 0;
    int currentTime = 0;
    int newTime;
    int counter = 0;
    int pushed = 0;

    while (getchar() != '\n'){
        note.id = (char*)calloc(11, sizeof(char));
        scanf("%[^/]/%d/%d", note.id, &(note.ta), &(note.ts));

        do{

            makeConditions(N, qs, &cs[moment], currentTime);
            newTime = currentTime;
            pushed = step(N, qs, &note, &newTime);

            if (pushed == -1)
                return -1;

            if (newTime != currentTime)
                moment += 1;

            if (moment > csNum - 1)
                return -2;
            currentTime = newTime;
        } while(!pushed);
    }

    while (MinTS(N, qs) != -1){
        makeConditions(N, qs, &cs[moment], currentTime);
        step(N, qs, NULL, &currentTime);
        moment ++;
        if (moment > csNum - 1)
            return -2;
    }
    if (moment > csNum - 1)
        return -2;
    makeConditions(N, qs, &cs[moment], currentTime);
    return moment + 1;
}

int step(int N, Queue* qs, Note *note, int *currentTime){
    int minTS;
    int pushed = 0;


    minTS = MinTS(N, qs);
    if (note == NULL){
        decreaseTS(N, qs, minTS);
        clearDone(N, qs);
        *currentTime += minTS;
        return 0;
    }

    if (minTS == -1){ //Если очереди пустые
        pushed = push(*note, qs);
        if (!pushed)
            return -1;
        *currentTime = note->ta;
    }
    else{
        if (note->ta - *currentTime <= minTS){ //Если посетитель пришел раньше, чем кто-то ушел
            pushed = push(*note, MinQueue(N, qs));
            if (!pushed)
                return -1;

            if (note->ta - *currentTime > 0){ // Если посететель пришел одновременно с предыдущим
                decreaseTS(N, qs, note->ta - *currentTime);
                if (MinTS(N, qs) == 0){ // Если посетитель пришел и одновременно кто-то ушел
                    clearDone(N, qs);
                }
                *currentTime = note->ta;
            }
        }
        else { //Если кто-то ушел, до того как кто-то пришел
            decreaseTS(N, qs, minTS);
            clearDone(N, qs);
            *currentTime += minTS;
        }
    }
    return pushed;
}

void clearDone(int N, Queue *qs){
    int i;
    for (i = 0; i < N; i++){
        if (qs[i].currentTS == 0)
            pull(&(qs[i]));
    }
}

void decreaseTS(int N, Queue* qs, int time){
    int i;

    for (i = 0; i < N; i++)
        qs[i].currentTS -= time;
}

int MinTS(int N, Queue* qs){
    int flag = 1; // Проверка на то что все очереди пустые
    int i;
    int min;

    for (i = 0; i < N; i++){
        if (qs[i].n != 0){
            if (flag == 1){
                min = qs[i].currentTS;
                flag = 0;
            } else if (qs[i].currentTS < min)
                min = qs[i].currentTS;
        }
    }
    if (flag == 1)
        return -1;
    return min;
}

Queue* MinQueue(int N, Queue* qs){
    int i;
    int min;
    Queue* currQ = qs;

    min = qs[0].totalTS;
    if (qs->n == 0){
        return qs;
    }

    for (i = 1; i < N; i++){
        if (qs[i].n == 0){
            return &(qs[i]);
        }
        if (qs[i].totalTS < min) {
            min = qs[i].totalTS;
            currQ = &(qs[i]);
        }
    }
    return currQ;
}







