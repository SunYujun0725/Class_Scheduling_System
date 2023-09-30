#ifndef BASIC_H
#define BASIC_H
#include "struct.h"
Course *search(Course *head, const char *name); //根據名稱找尋並回傳此指標
void add_course(Course *head, char *Name, char *Location, int room_number, char *week, int begin_hours, int begin_minutes, int end_hours, int end_minutes, double difficult, double course_credit);
void delete_course(Course *head, char *name);
void print_all(Course *head);                   //印出全部課程(Traverse)
int time_to_min(Course *p);                     //將開始時間轉成分鐘型態(sort用)
void sort(Course *head);                        //排序（依照開始時間排）
void set_node(Course *p);                       //初始化
void print_single(Course *p);                   //印出一個只是方便看
#endif
