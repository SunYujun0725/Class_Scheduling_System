#ifndef STRUCT_H
#define STRUCT_H
#include <cstdbool>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD 50
#define MAX_WEEK_WORD 10

typedef struct
{
    char week[MAX_WEEK_WORD];
    int begin_hours, begin_minutes, end_hours, end_minutes;
} _time;

struct _Course
{
    char course_name[MAX_WORD];    // (course name)
    char class_location[MAX_WORD]; // (classroom location)
    int classroom_number;

    _time time; // int[] (class time) 10:10=10.10

    double star; //(difficulty: star)
    double credits; // (credits)

    int week_to_int;

    struct _Course *next;
    struct _Course *prev;
};
typedef struct _Course Course;

struct _Student
{
    char student_name[MAX_WORD];
    char cannot_attend[5][MAX_WORD];         //該學生星期幾不能上課

};

struct a_found_course{
    int LCS_num;
    char course_name[MAX_WORD];
    struct a_found_course *right;
    struct a_found_course *left;
};

#endif