#include "Basic.h"
#include "struct.h"
#include "map.h"
#include "advanced_search.h"

//模板map
int xy[2][2];//存放初始地點和終點的xy座標
char visited[50][70];//紀錄該點是否被訪問過了：0->沒有走過,1->有走過
char map[50][70] ={ //真正大小為 38*64
{"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"},
{"@111111111111111111111111111111111111111-----------------------@"},
{"@        1       1            1      1-11----------------------@"},
{"@        1       1            1      1--1111111111111111111    @"},
{"@        1       1            1      1-----1  1     1------    @"},
{"@        1       1---         1      1-----1  1     1------    @"},
{"@        1       1---         1      1-----1  1     1-------   @"},
{"@        1       1------------1      1---  1  1     1--------  @"},
{"@        1       1------------1      1---  1  1     1----------@"},
{"@        1       1--------111111111111111111  1     1----------@"},
{"@        1       1-11111111---1      1     1  1    11----------@"},
{"@1111111111111111111     1----1      1     1  1    1-----------@"},
{"@---1----1----1---1      1----1      111111111111111-----------@"},
{"@---1----1----1---1      1----11111111     1-------------------@"},
{"@---1----1----1---1      1----1      1     1-------------------@"},
{"@1111111111111111111     1----1      11111111------------------@"},
{"@        1---------11111111---1      1      1------------------@"},
{"@        1------------11--111111111111      1------------------@"},
{"@        1       -----1-------1------1      1------------------@"},
{"@        1       ----1--      1------1      1------------------@"},
{"@        1       ----1--      1------11111111------------------@"},
{"@        1       ---11--      1      1------1------------------@"},
{"@        1       ---1---      1      1------1------------------@"},
{"@        1       -- 1  -      1      1-----11------------------@"},
{"@        1       -- 1  -      1      1----11-------------------@"},
{"@111111111111111111111111111111111111111111--------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@-----------------------------1--------------------------------@"},
{"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"}
};
int is_ed(Course *head,char *name){
    Course *p = search(head,name);
    if(p == NULL){
        return 0;
    }
    else if(strcmp(p->class_location,"edA")==0||strcmp(p->class_location,"edB")==0){
        return 1;
    }
    else{
        return -1;
    }
}
//把map重置才可以一直印
void reset_map(char (*temp)[70]){
    for(int i=0;i<50;i++){
        for(int j=0;j<70;j++){
            temp[i][j] = map[i][j];
            visited[i][j] = 0;
        }
    }
}
//把地點給特殊數字編號
int set_nameID(char *name){
    if(strcmp(name,"edA")==0||strcmp(name,"edB")==0){
        return 0;
    }
    else if(strcmp(name,"enA")==0){
        return 1;
    }
    else if(strcmp(name,"enB")==0){
        return 2;
    }
    else if(strcmp(name,"scA")==0||strcmp(name,"law")==0){
        return 3;
    }
    else if(strcmp(name,"scB")==0){
        return 4;
    }
    else if(strcmp(name,"soA")==0||strcmp(name,"soB")==0||strcmp(name,"hum")==0){
        return 5;
    }
    else if(strcmp(name,"inno")==0){
        return 6;
    }
    else if(strcmp(name,"man")==0){
        return 9;
    }
    else if(strcmp(name,"center")==0){
        return 11;
    }
    else if(strcmp(name,"gym")==0){
        return 12;
    }
    else if(strcmp(name,"lan")==0){
        return 8;
    }
    else{
        return -1;
    }
    
}

//0-> 同一地點 1->設置起點終點成功
int set_mapSD(char *Sn,char *Dn,char (*t_map)[70]){
    
    int start = set_nameID(Sn);
    int des = set_nameID(Dn);
    if(start == des){
        return 0;
    }
    else if(start <0 || des <0){
        return -1;
    }
    else{
        switch (start)
        {
        case 0:
            xy[0][0] = 11;
            xy[0][1] = 30;
            break;
        case 1:
            xy[0][0] = 12;
            xy[0][1] = 40;
            break;
        case 2:
            xy[0][0] = 8;
            xy[0][1] = 46;
            break;
        case 3:
            xy[0][0] = 4;
            xy[0][1] = 30;
            break;
        case 4:
            xy[0][0] = 4;
            xy[0][1] = 17;
            break;
        case 5:
            xy[0][0] = 22;
            xy[0][1] = 30;
            break;
        case 6:
            xy[0][0] = 3;
            xy[0][1] = 58;
            break;
        case 8:
            xy[0][0] = 13;
            xy[0][1] = 25;
            break;
        case 9:
            xy[0][0] = 18;
            xy[0][1] = 37;
            break;
        case 11:
            xy[0][0] = 25;
            xy[0][1] = 29;
            break;
        case 12:
            xy[0][0] = 11;
            xy[0][1] = 4;
            break;
        default:
            xy[0][0] = 0;
            xy[0][1] = 1;
            break;
        }
        switch (des)
        {
        case 0:
            xy[1][0] = 11;
            xy[1][1] = 30;
            break;
        case 1:
            xy[1][0] = 12;
            xy[1][1] = 40;
            break;
        case 2:
            xy[1][0] = 8;
            xy[1][1] = 46;
            break;
        case 3:
            xy[1][0] = 4;
            xy[1][1] = 30;
            break;
        case 4:
            xy[1][0] = 4;
            xy[1][1] = 17;
            break;
        case 5:
            xy[1][0] = 22;
            xy[1][1] = 30;
            break;
        case 6:
            xy[1][0] = 3;
            xy[1][1] = 58;
            break;
        case 8:
            xy[1][0] = 13;
            xy[1][1] = 25;
            break;
        case 9:
            xy[1][0] = 18;
            xy[1][1] = 37;
            break;
        case 11:
            xy[1][0] = 25;
            xy[1][1] = 29;
            break;
        case 12:
            xy[1][0] = 11;
            xy[1][1] = 4;
            break;
        default:
            xy[1][0] = 0;
            xy[1][1] = 1;
            break;
        }
        int x = xy[0][0];
        int y = xy[0][1];
        t_map[x][y] = 'S';
        x = xy[1][0];
        y = xy[1][1];
        t_map[x][y] = 'D';
        return 1;
    }
}

// DFS
struct path
{
    int x;
    int y;
    char temp_m[1];
} temp_path[1000000], short_p_min[1000000]; //紀錄路徑的struct
int path_k = 1;
int step_min = 1000000;

int dirs[4][2] = {
    {1, 0}, {-1, 0}, {0, -1}, {0, 1}};

void reset_DFS()
{
    path_k = 1;
    step_min = 1000000;
    for (int i = 0; i < 1000000; i++)
    {
        temp_path[i].x = 0;
        temp_path[i].y = 0;
        short_p_min[i].x = 0;
        short_p_min[i].y = 0;
    }
}
void store_path()
{
    memset(short_p_min, 0, sizeof(short_p_min)); //初始化結構，並將暫存的路徑存到short_p_min
    for (int i = 1; i < step_min; i++)
    {
        short_p_min[i] = temp_path[i];
    }
}

void DFS(int x, int y, int step, char (*temp)[70])
{
    if (temp[x][y] == 'D') //走到終點了
    {
        if (step < step_min)
        { //判斷最短路徑要走幾步
            step_min = step;
            store_path();
        }
        return;
    }
    for (int i = 0; i <= 3; i++)
    { // 考慮 (x,y) 周圍上、下、左、右四個方向
        if ((temp[x + dirs[i][0]][y + dirs[i][1]] == '1' || temp[x + dirs[i][0]][y + dirs[i][1]] == 'D') && visited[x + dirs[i][0]][y + dirs[i][1]] == 0)
        { //該點可以走且未訪問過
            if (x + dirs[i][0] >= 0 && x + dirs[i][0] < 38 && y + dirs[i][1] >= 0 && y + dirs[i][1] < 64)
            {                                         //確認該點在合理範圍內
                temp_path[path_k].x = x + dirs[i][0]; //紀錄路經的x座標
                // temp_path[path_k++].y = y + dirs[i][1]; //紀錄路經的y座標
                temp_path[path_k].y = y + dirs[i][1]; //紀錄路經的y座標
                if (i == 0)
                {
                    strcpy(temp_path[path_k++].temp_m, "v");
                }
                else if (i == 1)
                {
                    strcpy(temp_path[path_k++].temp_m, "^");
                }
                else if (i == 2)
                {
                    strcpy(temp_path[path_k++].temp_m, "<");
                }
                else if (i == 3)
                {
                    strcpy(temp_path[path_k++].temp_m, ">");
                }

                visited[x + dirs[i][0]][y + dirs[i][1]] = 1;
                DFS(x + dirs[i][0], y + dirs[i][1], step + 1, temp);
                visited[x + dirs[i][0]][y + dirs[i][1]] = 0; //回朔
                path_k--;                                    //回朔
            }
        }
    }
}

//印出地圖
void p_map(char (*temp)[70], FILE *fp1)
{
    for (int i=0; i<38; i++) {
        for (int j=0; j<64; j++) {
            fprintf(fp1, "%c", map[i][j]);
        }
        fprintf(fp1, "\n");
    }
    for (int i = 1; i < step_min; i++)
    {
        int x = short_p_min[i].x;
        int y = short_p_min[i].y;
        if (!strcmp(short_p_min[i].temp_m, "v"))
        {
            temp[x][y] = 'v';
        }
        else if (!strcmp(short_p_min[i].temp_m, "^"))
        {
            temp[x][y] = '^';
        }
        else if (!strcmp(short_p_min[i].temp_m, "<"))
        {
            temp[x][y] = '<';
        }
        else if (!strcmp(short_p_min[i].temp_m, ">"))
        {
            temp[x][y] = '>';
        }
        // temp[x][y] = '*'; //将最短路径标记在路径地图中
    }
    for (int i = 0; i < 38; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            printf("%c  ", temp[i][j]);
            fprintf(fp1, "%c  ", temp[i][j]);
        }
        printf("\n");
        fprintf(fp1, "\n");
    }
}

//找出最短路徑
void SP_ED(Course *head, char *start, char *des, FILE *fp1)
{
    Course *pS = advanced_search(head, start);
    Course *pD = advanced_search(head, des);
    if (pS == NULL || pD == NULL)
    {
        printf("輸入沒有的課程，印不出地圖...\n");
    }
    else
    {
        char temp_map[50][70];
        reset_map(temp_map);
        int success = set_mapSD(pS->class_location, pD->class_location, temp_map);
        if (success)
        {
            reset_DFS();
            DFS(xy[0][0], xy[0][1], 0, temp_map);
            printf("開始走的x座標:%d 開始走的y座標:%d 終點的x座標:%d 終點的y座標:%d\n", xy[0][0], xy[0][1], xy[1][0], xy[1][1]);
            if (step_min == 1000000)
            {
                printf("沒辦法走到終點\n");
            }
            else
            {
                printf("最短路徑要走：%d 步\n", step_min);
            }
            p_map(temp_map, fp1);
        }
        else if (success == 0)
        {
            printf("不需要移動地區，在同一個地方上課喔!\n");
        }
        else
        {
            printf("輸入的其中一個課程的地點沒有出現在學校地圖中,可以利用SEARCH做確認喔\n");
        }
    }
}
