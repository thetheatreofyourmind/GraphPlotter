#define WIDTH 80
#define HEIGHT 25
#define UPPER_BORDER_Y 1.0
#define LOWER_BORDER_Y -1.0
#define LOWER_BORDER_X 0.0
#define UPPER_BORDER_X (4 * PI)

int* get_values(char** rev_polish_record);
void draw_field(const int* values);