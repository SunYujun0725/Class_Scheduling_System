#include "struct.h"
#include "Basic.h"
#include "search_keyword.h"
#include "DP_Select.h"

/*---------------以下是linear search--------------------*/
void search_print_single(Course *p){
    printf("%s %s %d %s %d:%d %d:%d %lf %lf\n", p->course_name, p->class_location, p->classroom_number, p->time.week, p->time.begin_hours, p->time.begin_minutes, p->time.end_hours, p->time.end_minutes, p->star, p->credits);
}

void search_time(Course *head,int week,int hour,int min){
    int flag = 0;
    Course *p = head->next;
    int target_min;
    int cur_start_min;
    int cur_end_min;
    if(week==0)//只輸入時間
        target_min =hour * 60 + min;
    else//輸入星期
        target_min = (week - 1) * 24 * 60 + hour * 60 + min;
    for (; p != NULL;p=p->next){
        if(week==0){
            cur_start_min = p->time.begin_hours * 60 + p->time.begin_minutes;
            cur_end_min = p->time.end_hours * 60 + p->time.end_minutes;
        }
        else{
            cur_start_min = start_time_to_min(p);
            cur_end_min = end_time_to_min(p);
        }    
        if(target_min >= cur_start_min && target_min <= cur_end_min){
            search_print_single(p);
            flag = 1;
        }
    }
    if(flag == 0){
        printf("Nothing!\n");
    }
}

void search_week(Course *head,char *week){
    int flag = 0;
    Course *p = head->next;
    for (; p != NULL;p=p->next){
        if(!strcmp(p->time.week,week)){
            search_print_single(p);
            flag = 1;
        }
    }
    if(flag == 0){
        printf("Nothing!\n");
    }
}

void search_location(Course *head, char * location){
    int flag = 0;
    Course *p = head->next;
    for (; p != NULL;p=p->next){
        if(!strcmp(p->class_location,location)){
            search_print_single(p);
            flag = 1;
        }
    }
    if(flag == 0){
        printf("Nothing!\n");
    }
}

void search_room_number(Course *head,int number){
    int flag = 0;
    Course *p = head->next;
    for (; p != NULL;p=p->next){
        if(p->classroom_number == number){
            search_print_single(p);
            flag = 1;
        }
    }
    if(flag == 0){
        printf("Nothing!\n");
    }
        
}

void search_star_and_credits(Course *head,double number,int mode){
    int flag = 0;
    Course *p = head->next;
    if(mode==0){//star、credits一起搜尋
        for (; p != NULL;p=p->next){
            if(p->credits==number || p->star==number){
                search_print_single(p);
                flag = 1;
            }
        }
    }
    if(mode==1){//搜尋star
        for (; p != NULL;p=p->next){
            if(p->star==number){
                search_print_single(p);
                flag = 1;
            }
        }
    }
    if(mode==2){//搜尋credits
        for (; p != NULL;p=p->next){
            if(p->credits==number){
                search_print_single(p);
                flag = 1;
            }
        }
    }
    
    if(flag == 0){
        printf("Nothing!\n");
    }
}

void search_name(Course *head,char *name){
    int flag = 0;
    Course *p = head->next;
    for (; p != NULL;p=p->next)
        if(!strcmp(p->course_name,name)){
            search_print_single(p);
            flag = 1;
        }
    if(flag == 0){
        printf("Nothing!\n");
    }
}

/*------------------以下是運作search的輔助功能----------------------*/
int check_str_week(char *str){
    int week_to_int = 0;
    if(!strcmp(str,"Monday"))
        week_to_int = 1;
    if(!strcmp(str,"Tuesday"))
        week_to_int = 2;
    if(!strcmp(str,"Wednesday"))
        week_to_int = 3;
    if(!strcmp(str,"Thursday"))
        week_to_int = 4;
    if(!strcmp(str,"Friday"))
        week_to_int = 5;
    return week_to_int;
}

int char_to_int(char *str){//把string換成int
    int ans_char_to_int = 0;
    int multiplier_char_to_int=1;
    for (int i = 0; i < strlen(str);i++){
        ans_char_to_int += (str[strlen(str) - 1 - i] - '0')*multiplier_char_to_int;
        multiplier_char_to_int *= 10;
    }
    return ans_char_to_int;
}

double char_to_double(char *str){//把string換成int
    double ans_char_to_double=0;
    double multiplier_char_to_double = 1;
    for (int i = 1; i < strlen(str)-1;i++){//將'.'移除
        str[i] = str[i + 1];
        str[i + 1] = 0;
    }
    for (int i = 0; i < strlen(str); i++){
        ans_char_to_double += (str[i] - '0') * multiplier_char_to_double;
        multiplier_char_to_double *= 0.1;
    }
    return ans_char_to_double;
}

int divided(char *input,char input2[5][20]){//把輸入的string遇到空格就拆開
    int count = 0;
    int start=0;
    for (int i = 0; i <= strlen(input);i++){
        if(!((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= '0' &&  input[i]<= '9'))){
            for (int j = 0; j < (i - start);j++){
                input2[count][j] = input[j+start];
                if(j==i-start-1)
                    input2[count][j + 1] = '\0';
            }
            count++;  
            start = i + 1;
        }
    }
    return count;
}

/*-------------------search執行-----------------------*/
void search_execute(Course *head,char *search_input,char divided_search_input[10][20]){
    for (int i = 0; i < 10;i++)
        divided_search_input[i][0] = '\0';
    int input_cnt = divided(search_input, divided_search_input);
    int input_week_to_int = 0;
    int length = 0;
    //search_input[strlen(search_input)-1] = '\0';//去掉\n
    //printf("divided input is:%s %s\n",divided_search_input[0],divided_search_input[1]);
    if((input_week_to_int=check_str_week(divided_search_input[0]))!=0){//第一格是禮拜
        //printf("in week & time\n");
        if(divided_search_input[1][0]>='0' && divided_search_input[1][0]<='9'){//後面有指定時間
            if(input_cnt>3){
                printf("output:\n");
                printf("Nothing\n");
                return;
            }
            printf("output:\n");
            search_time(head, input_week_to_int, char_to_int(divided_search_input[1]), char_to_int(divided_search_input[2]));
        }
        else{//沒有指定時間
            printf("output:\n");
            search_week(head, search_input);
        }
    }
    else if(divided_search_input[0][0]>='0' && divided_search_input[0][0]<='9' && divided_search_input[1][0]>='0' && divided_search_input[1][0]<='9' && search_input[1]!='.'){//直接輸入時間
        //printf("in time\n");
        printf("output:\n");
        search_time(head, 0, char_to_int(divided_search_input[0]), char_to_int(divided_search_input[1]));
    }
    
    //
    else if(!strcmp(search_input,"center") || !strcmp(search_input,"inno") || !strcmp(search_input,"edA") || !strcmp(search_input,"edB") || !strcmp(search_input,"enA") || !strcmp(search_input,"enB") || !strcmp(search_input,"scA") || !strcmp(search_input,"scB") || !strcmp(search_input,"soA") || !strcmp(search_input,"soB") || !strcmp(search_input,"law") || !strcmp(search_input,"lan") || !strcmp(search_input,"man") || !strcmp(search_input,"hum") || !strcmp(search_input,"gym")){ //教室位置
        //printf("in location\n");
        if(input_cnt>1){
            printf("output:\n");
            printf("Nothing!\n");
            return;
        }
        printf("output:\n");
        search_location(head, search_input);
    }
    else if(search_input[0]>='A' && search_input[0]<='z' && input_cnt==1){//是英文字的只剩教室名字
        //printf("in course name\n");
        printf("output:\n");
        search_name(head, search_input);
    }
    else if(search_input[0]>='0' && search_input[0]<='9' && (length=strlen(search_input))>2 && search_input[1] != '.' && input_cnt==1){//教室號碼
        //printf("in room number\n");
        if(input_cnt>1){
            printf("output:\n");
            printf("Nothing!\n");
            return;
        }
        printf("output:\n");
        search_room_number(head, char_to_int(search_input));
    }
    else if((divided_search_input[0][0]>='0' && divided_search_input[0][0]<='9') || (divided_search_input[1][0]>='0' && divided_search_input[1][0]<='9')){//難度或學分數
        //printf("in star & credits\n");
        if(!strcmp(divided_search_input[0],"star") || !strcmp(divided_search_input[0],"stars")){
            printf("output:\n");
            search_star_and_credits(head, char_to_double(divided_search_input[1]), 1);
        }
        else if(!strcmp(divided_search_input[1],"star") || !strcmp(divided_search_input[1],"stars")){
            printf("output:\n");
            search_star_and_credits(head, char_to_double(divided_search_input[0]), 1);
        }
        else if(!strcmp(divided_search_input[0],"credit") || !strcmp(divided_search_input[0],"credits")){
            printf("output:\n");
            search_star_and_credits(head, char_to_double(divided_search_input[1]), 2);
        }
        else if(!strcmp(divided_search_input[1],"credit") || !strcmp(divided_search_input[1],"credits")){
            printf("output:\n");
            search_star_and_credits(head, char_to_double(divided_search_input[0]), 2);
        }
        else{
            printf("output:\n");
            search_star_and_credits(head, char_to_double(search_input),0);
        }
    }
    else{
        printf("output:\n");
        printf("Nothing!\n");
    }
}