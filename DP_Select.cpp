#include "DP_Select.h"
#include "Basic.h"

void add_curriculum(Course *class_head, Course *curriculm, int max_cp_A)
{
    Course *p = class_head;
    int i = 0;
    for (; p != NULL; p = p->next)
    {
        i++;
        if (i == max_cp_A + 1)
        {
            add_course(curriculm, p->course_name, p->class_location, p->classroom_number, p->time.week, p->time.begin_hours, p->time.begin_minutes, p->time.end_hours, p->time.end_minutes, p->star, p->credits);
        }
    }
}

void delete_cannot_time(Course *class_head, char *week)
{
    Course *pre, *cur = class_head;

    while (1)
    {
        if (!strcmp(cur->time.week, week))
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
            return;
        }

        pre = cur;
        cur = cur->next;
    }
}

int count_course(Course *head)
{
    int count = 0;
    Course *p = head;
    for (; p != NULL; p = p->next)
    {
        count++;
    }
    return count;
}

int start_time_to_min(Course *p)
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

int end_time_to_min(Course *p)
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
    time_min = (p->time.end_hours + p->week_to_int) * 60 + p->time.end_minutes; //轉成分鐘
    return time_min;
}

void course_select(Course *head, int i, struct _Student Student[], int cannot_days, int already_course)
{

    Course *creat_course = (Course *)malloc(sizeof(Course));
    Course *class_head = creat_course;
    set_node(class_head);
    Course *creat = head->next;                //要創一個新的linked list
    int total_course = count_course(head);     //算總course的數量（會多加一個前面的NULL）
    for (; creat != NULL; creat = creat->next) //複製原本有的課到新創的linked list
    {
        total_course++;
        add_course(class_head, creat->course_name, creat->class_location, creat->classroom_number, creat->time.week, creat->time.begin_hours, creat->time.begin_minutes, creat->time.end_hours, creat->time.end_minutes, creat->star, creat->credits);
    }
    for (int k = 0; k < cannot_days; k++) //針對該學生不行的日子去刪掉course
    {
        for (int l = 0; l < total_course; l++)
        {
            delete_cannot_time(class_head, Student[i].cannot_attend[k]);
        }
    }
    int select_total_course = count_course(class_head); //算刪完後的course數量（會多加一個前面的NULL）

    // Dynamic Programming 選擇課程
    double activity[select_total_course - 1];
    double start[select_total_course - 1];
    double finish[select_total_course - 1];
    double cp[select_total_course - 1];
    double H[select_total_course - 1];
    double A[select_total_course - 1];
    sort(class_head);
    Course *p = class_head->next;
    for (int k = 0; p != NULL; p = p->next, k++)
    {
        activity[k] = k + 1;
    }
    p = class_head->next;
    for (int k = 0; p != NULL; p = p->next, k++)
    {
        start[k] = start_time_to_min(p);
    }
    p = class_head->next;
    for (int k = 0; p != NULL; p = p->next, k++)
    {
        finish[k] = end_time_to_min(p);
    }
    p = class_head->next;
    for (int k = 0; p != NULL; p = p->next, k++)
    {
        cp[k] = (p->credits) / (p->star); // cp值為學分除以難度
    }
    p = class_head->next;
    for (int k = 0; p != NULL; p = p->next, k++)
    {
        int max_h = -1;
        int H_value = 0;
        if (k == 0)
        {
            H[k] = 0;
        }
        else
        {
            for (int l = 0; l <= k - 1; l++)
            {
                if (finish[l] <= start[k])
                {
                    if (max_h < finish[l])
                    {
                        max_h = finish[l];
                        H_value = l + 1;
                    }
                }
            }
            H[k] = H_value;
        }
    }
    p = class_head->next;
    for (int k = 0; p != NULL; p = p->next, k++)
    {
        if (H[k] == 0)
        {
            A[k] = cp[k];
        }
        else
        {
            int temp = H[k];
            if (A[k - 1] > cp[k] + A[temp - 1])
            {
                A[k] = A[k - 1];
            }
            else
            {
                A[k] = cp[k] + A[temp - 1];
            }
        }
    }
    double max_A = A[0];
    int max_cp_A = 0;
    for (int l = 0; l < select_total_course - 1; l++)
    {
        if (max_A <= A[l])
        {
            max_A = A[l];
            max_cp_A = l + 1;
        }
    }
    Course *newcurriculum = (Course *)malloc(sizeof(Course)); //創一個新的linked list，放該學生選擇後的課
    Course *curriculm = newcurriculum;
    set_node(curriculm);
    while (1)
    {
        if (H[max_cp_A - 1] == 0)
        {
            add_curriculum(class_head, curriculm, max_cp_A);
            break;
        }
        else
        {
            add_curriculum(class_head, curriculm, max_cp_A);
            max_cp_A = H[max_cp_A - 1];
        }
    }
    sort(curriculm);
    print_all(curriculm); //印出已經排好的課表
}

