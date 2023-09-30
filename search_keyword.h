#ifndef SEARCH_KEYWORD_H
#define SEARCH_KEYWORD_H
#include "struct.h"
#include "Basic.h"
void search_print_single(Course *p);
void search_time(Course *head, int week, int hour, int min);
void search_week(Course *head, char *week);
void search_location(Course *head, char *location);
void search_room_number(Course *head, int number);
void search_star_and_credits(Course *head, double number, int mode);
void search_name(Course *head, char *name);
int check_str_week(char *str);
int char_to_int(char *str);
double char_to_double(char *str);
int divided(char *input, char input2[5][20]);
void search_execute(Course *head, char *search_input, char divided_search_input[10][20]);
#endif