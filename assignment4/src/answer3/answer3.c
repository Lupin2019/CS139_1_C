/*
 * @Author: mathis 
 * @Date: 2021-12-23 00:25:57 
 * @Last Modified by:   mathis 
 * @Last Modified time: 2021-12-23 00:25:57 
 */
#include "list.h"
#include <stdio.h>
#include "param_deliver.h"


/**
 * @description: 
 * @param {LinkList*} list
 * @param {size_t} n
 * @return {*}
 */
void load_from_keyboard(LinkList* list, size_t n){
    Data data_buf;
    int length = 16;
    for(size_t i = 0; i < n; i++){
        // printf("Creating %ld/%ld:\n",i+1,n);
        data_buf = DataInitKeyboard();
        LinkListCreate(list, 0, &data_buf);
    }
}


/**
 * @description: 
 * @param {LinkList*} list
 * @param {FILE*} fp
 * @param {item_id} id
 * @return {*}
 */
void display_sorted_record(LinkList* list, FILE* fp, item_id id){
    LinkListSortByScore(list);
    LinkListPrintById(list, fp, id);
    
}



int main(){
    // input data by keyboard or by txt file
    LinkList *list = LinkListInit();
    printf("load from ../data/ table.txt is highly recommanded\n");
    char ch;
    printf("Do you have to input data from keyboard? (y/n)");
    scanf("%c", &ch);
    if(ch == 'y'|| ch =='Y'){
        load_from_keyboard(list, 10);
    }else{
        char data_path[100];
        strcpy(data_path, PROJECT_PATH);
        strcat(data_path, "/data/table20_d.txt");
        load_from_data_dir(list, data_path, 10);
    }

    // display
    LinkListPrintById(list, stdout, ALL);
    // display after sorted
    display_sorted_record(list, stdout, NAME);
    LinkListDeinit(list);
    return 0;
} 
