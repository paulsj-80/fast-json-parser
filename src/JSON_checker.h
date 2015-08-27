#ifndef JSON_CHECKER_H
#define JSON_CHECKER_H

/* JSON_checker.h */

#define JSON_TOKEN_KEY        10
#define JSON_TOKEN_VALUE      11
#define JSON_TOKEN_OBJ_START  13
#define JSON_TOKEN_OBJ_END    14
#define JSON_TOKEN_ARR_START  15
#define JSON_TOKEN_ARR_END    16

typedef int (*JSON_token_handler)(void *ctx, int type, int pos, int size);

typedef struct JSON_checker_struct {    
    int state;
    int depth;
    int top;
    int* stack;
    
    JSON_token_handler handler;
    void *handler_ctx;
    int curr_pos;
    int token_start_pos;
}* JSON_checker;


void reset_JSON_checker(JSON_checker jc, JSON_token_handler handler,
                        void *handler_ctx, int pos_offset);
int JSON_checker_char(JSON_checker jc, int next_char);
int JSON_checker_done(JSON_checker jc);


#endif
