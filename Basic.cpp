#include "Basic.h"
#include "struct.h"
//搜尋 根據名字找到課程
Course *search(Course *head, const char *name)
{
    Course *p = head;
    for (; p != NULL; p = p->next)
    {
        if (strcmp(p->course_name, name) == 0)
        {
            return p;
        }
    }
    return NULL; //沒找到
}

void add_course(Course *head, char *Name, char *Location, int room_number, char *week, int begin_hours, int begin_minutes, int end_hours, int end_minutes, double difficult, double course_credit)
{

    if(search(head,Name)==NULL){
        Course *newCourse = (Course *)malloc(sizeof(Course));
        strcpy(newCourse->course_name, Name);
        strcpy(newCourse->class_location, Location);
        newCourse->classroom_number = room_number;
        strcpy(newCourse->time.week, week);
        newCourse->time.begin_hours = begin_hours;
        newCourse->time.begin_minutes = begin_minutes;
        newCourse->time.end_hours = end_hours;
        newCourse->time.end_minutes = end_minutes;
        newCourse->next = NULL;
        newCourse->prev = NULL;
        newCourse->star = difficult;
        newCourse->credits = course_credit;

        Course *cur = head, *pre;
        while (1)
        {
            if (cur->next == NULL)
            {
                pre = cur;
                cur->next = newCourse;
                cur = cur->next;
                cur->next = NULL;
                cur->prev = pre;
                return;
            }
            pre = cur;
            cur = cur->next;
        }
    }

    else{
        printf("輸入的課程重複! 無法加入該課程\n");
    }
}

void delete_course(Course *head, char *name)
{
    Course *pre, *cur = head;

    while (1)
    {
        if (!strcmp(cur->course_name, name))
        {
            Course *t = cur;

            if (cur->next != NULL)
            {
                pre->next = cur->next;
                cur = cur->next;
                cur->prev = pre;
            }
            else
            {
                pre->next = NULL;
            }

            free(t);
            return;
        }

        if (cur->next == NULL)
        {
            printf("要刪除的課程不存在！\n");
            return;
        }

        pre = cur;
        cur = cur->next;
    }
}

void print_all(Course *head) //印出全部
{
    Course *p = head->next;
    for (; p != NULL; p = p->next)
    {
        printf("%s %s %d %s %d:%d %d:%d %lf %lf\n", p->course_name, p->class_location, p->classroom_number, p->time.week, p->time.begin_hours, p->time.begin_minutes, p->time.end_hours, p->time.end_minutes, p->star, p->credits);
    }
}

int time_to_min(Course *p)
{
    int time_min = 0;
    if (!strcmp(p->time.week, "Monday"))
    {
        p->week_to_int = 0;
    }
    else if (!strcmp(p->time.week, "Tuesday")) //如果是Tuesday就加一天24hr
    {
        p->week_to_int = 24;
    }
    else if (!strcmp(p->time.week, "Wednesday")) //如果是Wednesday就再加一天24hr＝48hr
    {
        p->week_to_int = 48;
    }
    else if (!strcmp(p->time.week, "Thursday"))
    {
        p->week_to_int = 72;
    }
    else if (!strcmp(p->time.week, "Friday"))
    {
        p->week_to_int = 96;
    }
    time_min = (p->time.begin_hours + p->week_to_int) * 60 + p->time.begin_minutes; //轉成分鐘
    return time_min;
}

void sort(Course *head)
{
    Course *p = head;
    int count = 0;
    p = p->next;
    for (; p != NULL; p = p->next)
    { //計算有幾個node，且判斷星期幾
        count++;
        // count_time(p);
    }
    Course *pre, *cur;
    for (int i = 0; i < count - 1; i++)
    {
        pre = head->next;
        for (int j = 0; j < count - i - 1; j++)
        {
            cur = pre->next;
            int compare1, compare2;
            compare1 = time_to_min(pre);
            compare2 = time_to_min(cur);

            // bubble sort(你原本寫的)
            if (compare1 > compare2)
            {
                cur->prev = pre->prev;
                pre->prev->next = cur;
                pre->prev = cur;
                pre->next = cur->next;
                if (cur->next != NULL)
                {
                    cur->next->prev = pre;
                }
                cur->next = pre;
            }
            else
            {
                pre = pre->next;
            }
        }
    }
}

void set_node(Course *p)
{
    p->next = NULL;
    p->prev = NULL;
    strcpy(p->course_name, "NULL");
    strcpy(p->class_location, "NULL");
    strcpy(p->time.week, "NULL");
    p->time.begin_hours = 0;
    p->time.begin_minutes = 0;
    p->time.end_hours = 0;
    p->time.end_minutes = 0;
    p->classroom_number = 0;
    p->star = 0;
    p->credits = 0;
    p->week_to_int = 0;
}

//印一個
void print_single(Course *p)
{

    printf("你擁有此課程，以下是它的資訊:\n");
    printf("%s %s %d %s %d:%d %d:%d %lf %lf\n", p->course_name, p->class_location, p->classroom_number, p->time.week, p->time.begin_hours, p->time.begin_minutes, p->time.end_hours, p->time.end_minutes, p->star, p->credits);
}
