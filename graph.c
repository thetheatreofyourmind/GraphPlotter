
#include <stdio.h>
#include <stdlib.h>

#include "calculation.h"
#include "draw_module.h"
#include "make_postfix.h"

int main() {
    printf("Enter an expression:\n");
    char* expr = NULL;
    char* expr_with_spaces = NULL;
    char** rev_polish_form = NULL;
    int* values = NULL;
    int tokennum = 0;
    if (!((expr = read_expr())&& (*expr)&&
          (expr_with_spaces = fill_spaces(expr)) &&
          (rev_polish_form = to_postfix(expr_with_spaces, &tokennum)) &&
          (values = get_values(rev_polish_form))))
        printf("Incorrect input! \n");
    else
        draw_field(values);
    free(expr);
    free(expr_with_spaces);
    free(rev_polish_form);
    free(values);
}