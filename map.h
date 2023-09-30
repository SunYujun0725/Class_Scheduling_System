#ifndef MAP_H
#define MAP_H
#include "Basic.h"
#include "struct.h"
#include "advanced_search.h"
int is_ed(Course *head,char *name);
void reset_map(char (*temp)[70]);
void p_map(char (*temp)[70], FILE *fp1);
void SP_ED(Course *head,char *name,char *name2, FILE *fp1);
void DFS(int x,int y,int step,char(*temp)[70]);
void min1();
#endif
