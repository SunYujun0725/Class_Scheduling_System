#include "struct.h"
#include "Basic.h"
#include "advanced_search.h"

//LCS
int max(int a, int b){
    if(a>=b)
        return a;
    else
        return b;
}

struct a_found_course *create_node_for_tree(int LCS_num, char course_name_[MAX_WORD]){
    struct a_found_course *new_node = (struct a_found_course *)malloc(sizeof(struct a_found_course));
    new_node->LCS_num = LCS_num;
    strcpy(new_node->course_name, course_name_);
    new_node->left = new_node->right = NULL;
    return new_node;
}

void create_tree(struct a_found_course** root, int LCS_num, char course_name[MAX_WORD]){
    struct a_found_course* temp = *root;

    if(temp==NULL){
        temp = create_node_for_tree(LCS_num, course_name);
    }

    //arranged by LCS_num
    else if(LCS_num<temp->LCS_num){
        return create_tree(&(temp->left), LCS_num, course_name);
    }
    
    else if(LCS_num>temp->LCS_num){
        return create_tree(&(temp->right), LCS_num, course_name);
    }    
    
    //when LCS_nums resemble
    else{
        //the order would be based on the length of the name of the course
        struct a_found_course *new_= create_node_for_tree(LCS_num, course_name);

        if(strlen(course_name) > strlen(temp->course_name)){
            if (temp->left != NULL){// insert
                new_->left = temp->left;
                temp->left = new_;
            }
            else{
                temp->left = new_;
            }
        }

        else{
            if (temp->right != NULL){
                new_->right = temp->right;
                temp->right = new_;
            }
            else{
                temp->right = new_;
            }
        }
        //what if courses have the same LCS_num and the same name length? -> possible?
    }
    *root = temp;
}

//for printing out
//reverse: to print out the most matched courses top 3
char* inorder_traversal_reverse(struct a_found_course* root){
    struct a_found_course *temp = root;

    if(temp!=NULL){
        inorder_traversal_reverse(temp->right);
        if(inorder_traversal_reverse(temp->right)){
            return inorder_traversal_reverse(temp->right);
        }
        else
            return temp->course_name;
    }

    return NULL;
}

char* find_courses(char* targeted_course_name, Course *head){
    int i, j; 
    int targeted_course_len = strlen(targeted_course_name);
    struct a_found_course *start = NULL;

    for (Course *temp = head->next; temp != NULL; temp=temp->next){
        int cmp_course_len = strlen(temp->course_name);
        char cmp_course_name[cmp_course_len];
        strcpy(cmp_course_name, temp->course_name);

        int square[targeted_course_len+1][cmp_course_len+1];

        for (i = 0; i < targeted_course_len+1; i++)
            square[i][0] = 0;
        for (j = 0; j < cmp_course_len+1; j++)
            square[0][j] = 0;

        for (i = 1; i < targeted_course_len+1; i++){
            for (j = 1; j < cmp_course_len+1; j++){
                if (tolower(targeted_course_name[i-1])==tolower(cmp_course_name[j-1])){
                    square[i][j] = square[i - 1][j - 1] + 1;
                }
                else {
                    square[i][j] = max(square[i][j - 1], square[i - 1][j]);
                }
            }
        }
        //binary search (tree)
        if(square[i-1][j-1]>0){
            create_tree(&start, square[i-1][j-1], cmp_course_name);
        }
    }

    return inorder_traversal_reverse(start);
}

Course* advanced_search(Course *head, char *targeted_course_name){
    char Y_N[3];
    char found[MAX_WORD];
    Course *p;
    p = search(head, targeted_course_name);

    if (p == NULL && find_courses(targeted_course_name, head)!=NULL)
    {
        strcpy(found, find_courses(targeted_course_name, head));
        printf("??��?????: %s\n", found);
        printf("輸�?? Y/N:");
        scanf("%s", Y_N);
        if (tolower(Y_N[0])=='y'){
            p = search(head, found);
            return p; 
        }
    }
    return p;
}