#ifndef DP_SELECT_H
#define DP_SELECT_H
#include "Basic.h"
#include "struct.h"
void course_select(Course *head, int i, struct _Student Student[], int cannot_days, int already_course);
int count_course(Course *head);                                           //計算course數量
void add_curriculum(Course *class_head, Course *curriculm, int max_cp_A); //新增一個course到課表內
void delete_cannot_time(Course *class_head, char *week);                  //刪掉該學生不行上課的課
int start_time_to_min(Course *p);                                         //將開始時間轉成分鐘型態
int end_time_to_min(Course *p);                                           //將結束時間轉成分鐘型態
#endif