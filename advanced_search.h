#ifndef ADVANCED_SEARCH_H
#define ADVANCED_SEARCH_H
#include "struct.h"
#include "Basic.h"

int max(int a, int b);                                                                  //比數字大小
struct a_found_course *create_node_for_tree(int LCS_num, char course_name_[MAX_WORD]);  //樹使用的node
void create_tree(struct a_found_course **root, int LCS_num, char course_name[MAX_WORD]);
char *inorder_traversal_reverse(struct a_found_course *root);                           //由多到少排出來
char *find_courses(char *targeted_course_name, Course *head);                           //LCS並用樹排
Course *advanced_search(Course *head, char *targeted_course_name);                      //找出字母最多一樣的名稱並回傳指標

#endif