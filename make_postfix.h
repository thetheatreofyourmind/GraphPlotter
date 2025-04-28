#define MAX_EXPR_LEN 100

enum tokentype { FUNC, OPBRACKET, CLBRACKET, VAL, OPER, ERROR };

enum tokentype deftoken(char* str);
const char* end_of_word(const char* str);
const char* end_of_num(const char* str);
char* fill_spaces(const char* src);
int priority(char* oper);
char** to_postfix(char* str, int* numtokens);
char* read_expr();