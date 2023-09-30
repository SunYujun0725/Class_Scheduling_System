#ifndef ALPHABET_SEQUENCE_H
#define ALPHABET_SEQUENCE_H
#include "struct.h"

int count_courses(Course *head);                                                        //數有幾堂課
void insert_course(Course *head, Course *be_inserted, Course *to_insert);               //插入課程
int cmp_letter(Course *a, Course *b);                                                   //比較字母大小
int binary_search(Course *head, int low, int high, Course *to_insert_node);             //依字母大小找課程要插在哪裡
void alphabet_sequence(Course *head);                                                   //依字母大小插入課程

#endif