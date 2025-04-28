#include "draw_module.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculation.h"

int* get_values(char** rev_polish_record) {
    int* values = (int*)malloc(WIDTH * sizeof(int));
    int error = 0;
    double step_y = (UPPER_BORDER_Y - LOWER_BORDER_Y) / (HEIGHT - 1);
    double step_x = (UPPER_BORDER_X - LOWER_BORDER_X) / (WIDTH - 1);
    if (values) {
        for (int i = 0; (error != 1) && i < WIDTH; i++) {
            double y = 2 * UPPER_BORDER_Y, x = step_x * i;
            error = calculate(rev_polish_record, x, &y);
            if (error == 2)
                values[i] = 2 * HEIGHT;
            else if (error == 0)
                values[i] = (int)round((y - LOWER_BORDER_Y) / step_y);
        }
    }
    if (error == 1) {
        free(values);
        values = NULL;
    }
    return values;
}

void draw_field(const int* values) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == values[j])
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}