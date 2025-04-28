#include "calculation.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "make_postfix.h"
#include "stack.h"

int odzctg(double x) { return (fabs(x / PI - round(x / PI)) < EPS) ? 0 : 1; }

int odztan(double x) { return odzctg(x - PI / 2); }

int str_to_func(char* funcname, double x, double* out) {
    int error = 0;
    if (!strcmp("sin", funcname))
        *out = sin(x);
    else if (!strcmp("cos", funcname))
        *out = cos(x);
    else if (!strcmp("sqrt", funcname) && x >= 0.0)
        *out = sqrt(x);
    else if (!strcmp("tan", funcname) && odztan(x))
        *out = tan(x);
    else if (!strcmp("ctg", funcname) && odzctg(x))
        *out = cos(x) / sin(x);
    else if (!strcmp("ln", funcname) && x > EPS)
        *out = log(x);
    else if (!strcmp("~", funcname))
        *out = -x;
    else
        error = 1;
    return error;
}

int str_to_oper(char* oper, double x1, double x2, double* result) {
    int error = 0;
    if (!strcmp(oper, "*"))
        *result = x1 * x2;
    else if (!strcmp(oper, "-"))
        *result = x1 - x2;
    else if (!strcmp(oper, "+"))
        *result = x1 + x2;
    else if (!strcmp(oper, "/") && x2 != 0.0)
        *result = x1 / x2;
    else
        error = 1;
    return error;
}

int calculate(char** expr, double x, double* output) {
    dstack* st = dinit();
    int error = 0;
    double result_of_operation = -1;
    for (; !error && *expr; expr++) {
        char* endptr = NULL;
        enum tokentype toktype = deftoken(*expr);
        if (toktype == VAL && !strcmp("x", *expr))
            dpush(st, x);
        else if (toktype == VAL)
            dpush(st, strtod(*expr, &endptr));
        else if (toktype == FUNC) {
            if (dis_empty(st))
                error = 1;
            else if (str_to_func(*expr, dpop(st), &result_of_operation))
                error = 2;
            else
                dpush(st, result_of_operation);
        } else if (toktype == OPER) {
            double x1 = -1, x2 = -1;
            if (dis_empty(st))
                error = 1;
            else
                x2 = dpop(st);
            if (dis_empty(st))
                error = 1;
            else
                x1 = dpop(st);
            if (!error && str_to_oper(*expr, x1, x2, &result_of_operation)) error = 2;
            if (!error) dpush(st, result_of_operation);
        }
    }
    if (error != 2) {
        if (dis_empty(st))
            error = 1;
        else
            *output = dpop(st);
        if (!dis_empty(st)) error = 1;
    }
    ddestroy(st);
    return error;
}
