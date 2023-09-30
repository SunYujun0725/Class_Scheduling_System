#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "Basic.h"
#include "struct.h"
#include "DP_Select.h"
#include "map.h"
#include "advanced_search.h"
#include "alphabet_sequence.h"
#include "search_keyword.h"

// global
char order[30]; //輸入的指令
struct _Student Student[50];
//插入課程名稱 1->2
void insert(Course *head,char *name,char *name2){
  Course *p =  search(head,name);
  Course *p2 = search(head,name2);
  Course *pre = p2->prev;
  if(p == NULL){
    printf("輸入的前一課堂為沒有的課程名稱喔，自動把插入課程排到最後面\n");
  }
  else{
    if(p->next != p2){
        pre->next = NULL;
        p->next->prev = p2;
        p2->next = p->next;
        p2->prev = p;
        p->next = p2;
    }
  }
}

// memset 變數 要不然後續的輸入值會被覆蓋掉
void mem_ALL(char name[], char week[], char location[],char name2[])
{
    memset(order, 0, sizeof(order));        //初始0
    memset(week, 0, sizeof(*week));         //初始0
    memset(name, 0, sizeof(*name));         //初始0
    memset(location, 0, sizeof(*location)); //初始0
    memset(name2, 0, sizeof(*name2));         //初始0
}
// list information把如何使用指令印出//可更改成更舒服的輸入方式 ADD/DELETE/LIST/INSERT/SORT
void print_inform()
{
    char T[2];
    printf("####   [指令內容區]   ####\n");
    if (strcmp(order, "ADD") == 0)
    {
        printf("ADD 指令模板如下:\n");
        printf("課程名稱｜上課地點｜教室號碼｜星期幾｜開始上課小時｜開始上課分鐘｜結束上課時｜結束上課分｜課程難度｜學分數\n");
        printf("地點名稱如下:\n");
        printf("[共教一二:edA/edB][工院一二:enA /enB][理院一二:scA/scB][社科一二:soA/soB][創新: inno]\n");
        printf("[管院:man][文院:hum][活中:center][體育館:gym][語中:lan][法學院:law]\n");
        printf("$$NOTICE:  時間是24小時制 也就是下午三點五分上課要輸入 15 | 05  $$\n");
    }
    else if (strcmp(order, "DELETE") == 0)
    {
        printf("DELETE 指令模板如下:\n");
        printf("[DELETE 課程名稱]\n");
    }
    else if (strcmp(order, "LIST") == 0)
    {
        printf("LIST 指令模板如下:\n");
        printf("[LIST]\n");
    }
    else if (strcmp(order, "INSERT") == 0)
    {
        printf("INSERT 指令模板如下:\n");
        printf("[INSERT 課程名稱A | 課程名稱B]");
        printf("$$NOTICE:  課程B會在課程A後面(**NAME_A->NAME_B**)$$\n");
    }
    else if (strcmp(order, "SORT") == 0)
    {
        printf("SORT 指令模板如下:\n");
        printf("[SORT]");
    }
    else if (strcmp(order, "SEARCH") == 0)
    {
        printf("SEARCH 指令模板如下:\n");
        printf("[SEARCH 課程名稱]\n");
    }
    else
    {
        printf("!!輸入錯誤 !!\nTry again?(Y/N): ");
        scanf("%s", T);
        if (strcmp(T, "Y") == 0 || strcmp(T, "YES") == 0)
        {
            printf("再次輸入想知道的指令名稱(不須再次輸入ORDER): ");
            memset(order, 0, sizeof(order));
            scanf("%s", order);
            print_inform();
        }
    }
}
// memset node to null 之後有想要memset的可以自行修改 目前只有設前後pointer和名稱 NULL
//多寫註解，要不然以後會看得很痛苦喔
//多寫提示

//token 將學生無法上課的日字用token分割
int token1(int i, char not_attend[])
{
    int str_long = strlen(not_attend);
    int k = 0, m = 0, count = 0;
    for (int j = 0; j < str_long; j++)
    {
        if (not_attend[j] != ' ' && not_attend[j] != '\n')
        {
            Student[i].cannot_attend[k][m] = not_attend[j];
            m++;
        }
        else if (not_attend[j] == ' ')
        {
            k++;
            m = 0;
            count++;
        }
        else if (not_attend[j] == '\n')
        {
            return count + 1;
        }
    }
    return count + 1;
}

int main()
{
    Course *newCourse = (Course *)malloc(sizeof(Course));
    Course *head = newCourse;
    set_node(head);
    //變數
    char name[MAX_WORD];
    char name2[MAX_WORD];
    char location[MAX_WORD];
    int room_number;
    char week[MAX_WEEK_WORD];
    char start[MAX_WORD];
    char end[MAX_WORD];
    int begin_hours;
    int begin_minutes;
    int end_hours;
    int end_minutes;
    double difficult;
    double course_credit;
    char running[20];
    //
    FILE *fp1, *fp2;
    fp1 = fopen("filename.txt", "w");
    fp2 = fopen("filename.txt", "r");
    //提示字
    printf("可輸入的指令(被'|'分割): ADD | DELETE | LIST | SORT | INSERT | SEARCH | MAP\n");
    printf("輸入ORDER NAME來獲得NAME相關的指令\n");
    printf("輸入END來結束輸入課表!\n");
    printf("請輸入指令:\n");
    //測試區 用指令方式 能比較方便用
    // while (scanf("%s", order) != EOF)
    scanf("%s", order);
    while (strcmp(order, "END"))
    {
        if (strcmp(order, "ORDER") == 0)
        {
            memset(order, 0, sizeof(order)); //初始0
            scanf("%s", order);              //吃名字
            print_inform();                  //印出指令template
            printf("####   [指令內容區]   ####\n");
        }
        else if (strcmp(order, "ADD") == 0)
        {
            printf("課程名稱｜上課地點｜教室號碼｜星期幾｜開始上課小時:分鐘｜結束上課時:分｜課程難度｜學分數\n");
            scanf("%s %s %d %s %s %s %lf %lf", name, location, &room_number, week, start,end, &difficult, &course_credit);
            if(start[2]!=':'||end[2]!=':'||start[5]!='\0'||end[5]!='\0'){
                printf("時間輸入模板錯誤,要輸入XX:XX(時:分),加入課程失敗\n");
            }
            else{
                char sh[3],sm[3],eh[3],em[3];
                for(int i=0;i<2;i++){
                    sh[i] = start[i];
                    eh[i] = end[i];
                }
                for(int i=3;i<5;i++){
                    sm[i-3] = start[i];
                    em[i-3] = end[i]; 
                }
                sh[2] = '\0';
                sm[2] = '\0';
                eh[2] = '\0';
                em[2] = '\0';
                add_course(head, name, location, room_number, week, atoi(sh), atoi(sm), atoi(eh), atoi(em), difficult, course_credit);
            }
            
        }
        else if (strcmp(order, "DELETE") == 0)
        {   
            printf("要刪除的課程名稱:\n");
            scanf("%s", name);
            delete_course(head, name);
        }
        else if (strcmp(order, "LIST") == 0)
        {
            strcpy(running,"listing");
            printf("%s.",running);
            sleep(1);
            printf("\r%s..",running);
            sleep(1);
            printf("\r%s completed!\n",running);
            sleep(1);
            print_all(head);
        }
        else if (strcmp(order, "INSERT") == 0) //有問題
        {
            printf("前一課程名稱:\n");
            scanf("%s",name);
            printf("插入的課程名稱｜上課地點｜教室號碼｜星期幾｜開始上課小時:分鐘｜結束上課小時:分鐘｜課程難度｜學分數\n"); 
            scanf("%s %s %d %s %s %s %lf %lf", name2, location, &room_number, week, start,end, &difficult, &course_credit);
            if(start[2]!=':'||end[2]!=':'||start[5]!='\0'||end[5]!='\0'){
                printf("時間輸入模板錯誤,要輸入XX:XX(時:分),加入課程失敗\n");
            }
            else{
                char sh[3],sm[3],eh[3],em[3];
                for(int i=0;i<2;i++){
                    sh[i] = start[i];
                    eh[i] = end[i];
                }
                for(int i=3;i<5;i++){
                    sm[i-3] = start[i];
                    em[i-3] = end[i]; 
                }
                sh[2] = '\0';
                sm[2] = '\0';
                eh[2] = '\0';
                em[2] = '\0';
                add_course(head, name2, location, room_number, week, atoi(sh), atoi(sm), atoi(eh), atoi(em), difficult, course_credit);
                insert(head,name,name2);
              }
        }
        else if (strcmp(order, "SORT") == 0)
        {
            char seq[MAX_WORD];
            printf("輸入排序偏好: TIME | ALPHABET\n");
            scanf("%s", seq);

            if(!strcmp(seq, "TIME") || !strcmp(seq, "ALPHABET")){
                strcpy(running,"sorting");
                printf("%s.",running);
                sleep(1);
                printf("\r%s..",running);
                sleep(1);
                printf("\r%s completed!\n",running);
                sleep(1);
            }

            if (!strcmp(seq, "TIME"))
            {   
                sort(head);
                print_all(head);
            }

            else if (!strcmp(seq, "ALPHABET")){
                alphabet_sequence(head);
                print_all(head);
            }

            else{
                printf("沒有此排序偏好選項\n");
            }
        }
        else if (strcmp(order,"SEARCH") == 0){
            //printf("search:\n");
            char search_input[50];
            char divided_search_input[10][20];
            printf("請輸入要搜尋的關鍵字(ex:課程名稱、上課時間、地點....)\n");
            getchar();
            gets(search_input);
            strcpy(running, "searching");
            printf("%s.", running);
            sleep(1);
            printf("\r%s..",running);
            sleep(1);
            printf("\r%s completed!\n",running);
            sleep(1);
            search_execute(head,search_input,divided_search_input);
        }
        else if (strcmp(order,"MAP") == 0){
            printf("請輸入:現在課程名稱|下堂課程名稱");
            scanf("%s %s",name,name2);
            SP_ED(head,name,name2,fp1);
        }
        else
        {
            printf("輸入錯誤了請再試一次!\nTry again!\n");
        }
        mem_ALL(name, week, location,name2);
        printf("請輸入指令:\n");
        scanf("%s", order);
    }
    
    for (int i = 0; i < 50; i++)
    {
        strcpy(Student[i].student_name, "\0");
        for (int j = 0; j < 5; j++)
        {
            strcpy(Student[i].cannot_attend[j], "\0");
        }
    }
    int student_number;
    char st_name[MAX_WORD];
    char not_attend[1000];
    char already[1000];
    printf("輸入學生人數：");
    scanf("%d", &student_number);
    int cannot_days[50] = {0};
    int already_course[50] = {0};
    printf("輸入學生資料\n");
    for (int i = 0; i < student_number; i++) //輸入學生資料
    {
        printf("學生名字｜該學生星期幾無法上課\n");
        scanf("%s\n", st_name);
        strcpy(Student[i].student_name, st_name);
        fgets(not_attend, 1000, stdin);
        cannot_days[i] = token1(i, not_attend);
       
    }

    for (int i = 0; i < student_number; i++)
    {
        printf("%s的課表如下:\n",Student[i].student_name);
        course_select(head, i, Student, cannot_days[i], already_course[i]);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
//(╯°Д°）╯︵ /(.□ . \)
//╭(°A°`)╮
