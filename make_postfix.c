#include "make_postfix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

char* read_expr() {
    char* expr = NULL;
    if ((expr = (char*)malloc(MAX_EXPR_LEN * sizeof(char)))) {
        char* ptr = expr;
        while (scanf("%c", ptr) && *ptr != '\n') ptr++;
        *ptr = '\0';
    }
    return expr;
}

enum tokentype deftoken(char* str) {
    enum tokentype result = ERROR;
    char* endptr = NULL;
    strtod(str, &endptr);
    if (endptr != str && *endptr == '\0')
        result = VAL;
    else if (!strcmp("+", str) || !strcmp("-", str) || !strcmp("*", str) || !strcmp("/", str))
        result = OPER;
    else if (!strcmp("sin", str) || !strcmp("cos", str) || !strcmp("sqrt", str) || !strcmp("tan", str) ||
             !strcmp("ctg", str) || !strcmp("ln", str) || !strcmp("~", str))
        result = FUNC;
    else if (!strcmp("x", str))
        result = VAL;
    else if (!strcmp(")", str))
        result = CLBRACKET;
    else if (!strcmp("(", str))
        result = OPBRACKET;
    else
        result = ERROR;
    return result;
}

const char* end_of_word(const char* str) {
    const char* ptr = str;
    while (*ptr <= 'z' && *ptr >= 'a') ptr++;
    return ptr;
}

const char* end_of_num(const char* str) {
    char* res = NULL;
    strtod(str, &res);
    return res;
}

char* fill_spaces(const char* src) {
    char* new_str = NULL;
    int error = 0;
    if (*src && !(new_str = (char*)malloc((strlen(src) * 2 + 1) * sizeof(char)))) error = 1;
    char* ires = new_str;
    const char* cur = src;
    while (!error && *cur) {
        const char* end = NULL;
        if (*cur <= 'z' && *cur >= 'a')
            end = end_of_word(cur);
        else if (*cur <= '9' && *cur >= '0')
            end = end_of_num(cur);
        else
            end = cur + 1;
        for (; cur != end; cur++, ires++) *ires = *cur;
        *ires = ' ';
        ires++;
    }
    *ires = '\0';
    return new_str;
}

int priority(char* oper) {
    int res = 0;
    if (!strcmp("*", oper) || !strcmp("/", oper))
        res = 2;
    else
        res = 1;
    return res;
}

char** to_postfix(char* str, int* numtokens) {
    char** res = NULL;
    *numtokens = 0;
    int error = 0;
    char* prev = NULL;
    stack* st = init();
    enum tokentype toktype = ERROR;
    if (!(res = (char**)malloc(sizeof(char*) * strlen(str)))) error = 1;
    char* token = strtok(str, " ");
    if(token)toktype = deftoken(token);
    if (toktype == ERROR) error = 1;
    while (!error && token) {
        if (toktype == VAL) {
            res[(*numtokens)++] = token;
            while (!is_empty(st) && deftoken(top(st)) == FUNC) res[(*numtokens)++] = pop(st);
        } else if (toktype == OPER && !strcmp("-", token) &&
                   !(prev && (deftoken(prev) == VAL || deftoken(prev) == CLBRACKET))) {
            *token = '~';
        }
        if (deftoken(token) == FUNC || toktype == OPBRACKET)
            push(st, token);
        else if (toktype == OPER) {
            while (!is_empty(st) && deftoken(top(st)) == OPER && priority(top(st)) >= priority(token))
                res[(*numtokens)++] = pop(st);
            push(st, token);
        } else if (toktype == CLBRACKET) {
            while (!is_empty(st) && deftoken(top(st)) != OPBRACKET) {
                res[(*numtokens)++] = pop(st);
            }
            if (is_empty(st))
                error = 1;
            else
                pop(st);
            while (!is_empty(st) && deftoken(top(st)) == FUNC) res[(*numtokens)++] = pop(st);
        }
        prev = token;
        token = strtok(NULL, " ");
        if (token) toktype = deftoken(token);
        if (token && toktype == ERROR) error = 1;
    }
    while (!error && !is_empty(st)) {
        if (deftoken(top(st)) == OPBRACKET) error = 1;
        res[(*numtokens)++] = pop(st);
    }
    if (res) res[*numtokens] = NULL;
    destroy(st);
    if (error) free(res);
    return error ? NULL : res;
}
