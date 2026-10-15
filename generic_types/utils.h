#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdbool.h>

extern char *strdup(const char *);
typedef bool check_func(char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
  char character;
} answer_t;

typedef answer_t convert_func(char *);
typedef struct item item_t;
typedef struct point point_t;

struct item {
    char *namn;
    char *beskrivning;
    int pris;
    char *id;
};

void clear_input_buffer(void);
int read_string(char *buf, int buf_siz);
bool is_number(char *str);
int ask_question_int(char *question);
char *ask_question_string(char *question);
char *ask_question_shelf(char *question);
char *print(char *string);
bool not_empty(char *str);
char *println(char *string);
bool is_valid_id(char *id);
char ask_question_menu(char* question);
void print_menu(void);
void remove_item_from_db(item_t *db, int *db_siz);
void list_db(item_t *items, int *no_items);
answer_t ask_question(char *question, check_func *check, convert_func *convert);
#endif 