#include "stack.h"

#include <stdlib.h>

stack* init() {
    stack* res = (stack*)malloc(sizeof(stack));
    res->head = NULL;
    return res;
}
int is_empty(stack* st) { return st->head ? 0 : 1; }

char* pop(stack* st) {
    char* val = st->head->str;
    nd* hd = st->head;
    st->head = hd->next;
    free(hd);
    return val;
}

void push(stack* st, char* adstr) {
    nd* hd = (nd*)malloc(sizeof(nd));
    hd->next = st->head;
    hd->str = adstr;
    st->head = hd;
}

char* top(stack* st) { return st->head->str; }

void destroy(stack* st) {
    while (!is_empty(st)) pop(st);
    free(st);
}

dstack* dinit() {
    dstack* res = (dstack*)malloc(sizeof(dstack));
    res->head = NULL;
    return res;
}
int dis_empty(dstack* st) { return st->head ? 0 : 1; }

double dpop(dstack* st) {
    double val = st->head->num;
    dnd* hd = st->head;
    st->head = hd->next;
    free(hd);
    return val;
}

void dpush(dstack* st, double adstr) {
    dnd* hd = (dnd*)malloc(sizeof(dnd));
    hd->next = st->head;
    hd->num = adstr;
    st->head = hd;
}

void ddestroy(dstack* st) {
    while (!dis_empty(st)) dpop(st);
    free(st);
}