#define PI 3.14159265358979323846
#define EPS 1e-10

int odzctg(double x);
int odztan(double x);
int str_to_func(char* funcname, double x, double* out);
int str_to_oper(char* oper, double x1, double x2, double* result);
int calculate(char** expr, double x, double* output);
