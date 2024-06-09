#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ping_max 10000
#define ping_min 1

typedef struct {
    int begin;
    int end;
    int *request;
} RecentCounter;

RecentCounter* recentCounterCreate() {
    RecentCounter* obj = malloc(sizeof(RecentCounter));
    obj->begin = 0;
    obj->end = ping_max;
    obj->request = (int *)malloc(obj->end * sizeof(int));
    return obj;
}

int recentCounterPing(RecentCounter* obj, int t) {
    obj->request[obj->begin++] = t;
    int count = 0;
    for(int i = 0;i < obj->begin;i++)
    {
        if(t - 3000 <= obj->request[i] && obj->request[i] <= t)
        {
            count++;
        }
    }
    return count;
}

void recentCounterFree(RecentCounter* obj) {
    free(obj->request);
    free(obj);
}

int main() {
    RecentCounter *obj = recentCounterCreate();
    int t;
    while (scanf("%d", &t) != EOF) {
        printf("%d\n", recentCounterPing(obj, t));
    }
    recentCounterFree(obj);
    return 0;
}
