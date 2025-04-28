#ifndef STACK_H
#define STACK_H

typedef struct node {
    char* str;
    struct node* next;
} nd;

typedef struct stack {
    struct node* head;
} stack;

stack* init();
int is_empty(stack* st);
char* pop(stack* st);
void push(stack* st, char* adstr);
char* top(stack* st);
void destroy(stack* st);

typedef struct dnode {
    double num;
    struct dnode* next;
} dnd;

typedef struct dstack {
    struct dnode* head;
} dstack;

dstack* dinit();
int dis_empty(dstack* st);
double dpop(dstack* st);
void dpush(dstack* st, double adstr);
void ddestroy(dstack* st);

#endif