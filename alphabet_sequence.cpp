#include "struct.h"
#include "alphabet_sequence.h"

//sort by alphabet
int count_courses(Course *head){
    Course *temp = head;
    int count=0;
    for (; temp->next != NULL; temp=temp->next){
        count++;
    }
    return count;
}

void insert_course(Course* head, Course* be_inserted, Course* to_insert){
    Course *be_pre=head, *to_pre=head;

    if (be_inserted==to_insert){
        return;
    }
    
    //to find _insert_'s previous node
    for (; be_pre->next != be_inserted; be_pre = be_pre->next) //; ? ;
        continue;

    for (; to_pre->next!=to_insert; to_pre=to_pre->next)
        continue;

    //insert
    to_pre->next = to_insert->next;
    to_insert->next = be_inserted;
    be_pre->next = to_insert;
}

int cmp_letter (Course* a, Course* b){
    char a_name[MAX_WORD];
    strcpy(a_name, a->course_name);
    char b_name[MAX_WORD];
    strcpy(b_name, b->course_name);
    int i = 0;

    //all convert to lowercase
    //use of undeclared identifier 'tolower'?
    int a_len = strlen(a_name);
    for (int j = 0; j < a_len; j++)
    {
        a_name[j] = tolower(a_name[j]);
    }

    int b_len = strlen(b_name);
    for (int j = 0; j < b_len; j++)
    {
        b_name[j] = tolower(b_name[j]); 
    }


    //to find the different letter location
    for (; i < MAX_WORD; i++)
    {
        if (a_name[i] != b_name[i]){
            break;
        }
    }

    //to compare letters at the location [i]
    if(a_name[i]>=b_name[i] || b_name[i]=='\r'){ // b_name will precede a_name
        return 0;
    }

    else if (a_name[i]<b_name[i] || a_name[i]=='\r'){ // b_name will be after a_name
        return 1;
    }

    return 1;
}

int binary_search(Course* head, int low, int high, Course* to_insert_node){
    Course *temp1=head->next, *temp_mid=head->next;
    int return_val;
    //to get the node located at low/highth
    for (int i = 0; i < low; i++){
        temp1 = temp1->next;
    }

    if (low >= high){   
        if(cmp_letter(temp1, to_insert_node)){ // if cmp_letter = 1, b_name will be after a_name
            return low + 1;
        }

        else{
            return low;
        }
    }
    else{ 
        int mid = (low + high) / 2; //operation '/': round down
        for (int i = 0; i < mid; i++){
            temp_mid = temp_mid->next;
        }

        if(!cmp_letter(temp_mid, to_insert_node)){ //if cmp_letter = 0, b_name will precede a_name
            return_val=binary_search(head, low, mid - 1, to_insert_node);
        }

        if(cmp_letter(temp_mid, to_insert_node)){
            return_val=binary_search(head, mid + 1, high, to_insert_node);
        }
    }
    return return_val;
}

void alphabet_sequence (Course *head){
    int count = count_courses(head);
    int loc;
    Course *to_insert_node, *temp;

    for (int i = 0; i < count-1; i++){
        to_insert_node=head->next;
        for (int j = 0; j < i + 1; j++){
            to_insert_node = to_insert_node->next;
        }
        
        loc=binary_search(head, 0, i, to_insert_node);
        temp = head->next;
        for (int j = 0; j < loc; j++){
            temp = temp->next;
        }
        insert_course(head, temp, to_insert_node);
    }
}