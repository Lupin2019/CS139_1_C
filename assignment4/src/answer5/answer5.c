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


void list_reverse(LinkList* list){
    //api
    LinkListReverse(list);
}


void demo_reverse(){
    LinkList *list = LinkListInit();
    printf("load from ../data/ table.txt is highly recommanded\n");
    char data_path[100];
    strcpy(data_path, PROJECT_PATH);
    strcat(data_path, "/data/table20_d.txt");
    load_from_data_dir(list, data_path, 10); 
    display_all(list);
    list_reverse(list);
    display_all(list);
    LinkListDeinit(list);
}


int main(){
    demo_reverse();
    return 0;
} 
