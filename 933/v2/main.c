#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ping_max 10000
#define ping_min 1

#define fmax(a,b) ((a)) > (b) ? (a) : (b)


typedef struct {
    int *request;
    int size;
    int front;
    int rear;
} RecentCounter;

RecentCounter* recentCounterCreate() {
    RecentCounter* obj = malloc(sizeof(RecentCounter));
    obj->request = (int *)malloc(ping_max * sizeof(int));
    obj->size = 0;
    obj->front = 0;
    obj->rear = 0;
    return obj;
}

int recentCounterPing(RecentCounter* obj, int t) {
    obj->request[obj->rear++] = t;
    obj->size = fmax(obj->size, obj->rear - obj->front);
    while (t - 3000 > obj->request[obj->front] && obj->front < obj->rear) {
        obj->front++;
        obj->size--;
    }
    return obj->size;
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
