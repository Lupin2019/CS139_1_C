/*
 * @Author: mathis 
 * @Date: 2021-12-23 00:25:57 
 * @Last Modified by:   mathis 
 * @Last Modified time: 2021-12-23 00:25:57 
 */
#include "list.h"
#include <stdio.h>
#include "param_deliver.h"

void display_all(LinkList* list){
    // api
    LinkListPrintById(list, stdout, ALL);
}


/**
 * @description: 
 * @param {size_t} pos: 0 means the tail, 
 * 1 means the new node will at 1st place
 * @return {*}
 */
void demo_append(LinkList* list, size_t pos){
    // api and api
    Data data = DataInitKeyboard();
    LinkListCreate(list, pos ,&data);
}


/**
 * @description: 
 * @param {LinkList*} list
 * @param {size_t} pos
 * @return {*}
 */
void demo_remove(LinkList* list, size_t pos){
    // api
    LinkListDelete(list, pos);
}


int main(){
    LinkList *list = LinkListInit();
    printf("load from ../data/ table.txt is highly recommanded\n");
    char data_path[100];
    strcpy(data_path, PROJECT_PATH);
    strcat(data_path, "/data/table20_d.txt");
    load_from_data_dir(list, data_path, 10);

    display_all(list);
    demo_append(list,0);
    display_all(list);
    demo_remove(list,1);
    display_all(list);
    
    LinkListDeinit(list);
    return 0;
} 
