/*
 * @Author: Mathis
 * @Date: 2021-12-22 22:39:42
 * @LastEditTime: 2021-12-25 20:53:13
 * @Description: file content
 * @FilePath: /assignment4/src/demo.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


void load_from_keyboard(LinkList* list, size_t n){
    Data data_buf;
    int length = 16;
    for(size_t i = 0; i < n; i++){
        printf("Creating %ld/%ld:\n",i+1,n);
        data_buf = DataInitKeyboard();
        LinkListCreate(list, 0, &data_buf);
    }
}


int main(){
    #if 1
    int N = 20;
    #if 1
    LinkList *list = LinkListInit();
    load_from_keyboard(list, N);
    LinkListPrintById(list, stdout, NAME);
    // int N = 20;
    FILE *fp;
    fp = fopen("./demo.txt","wb");
    Node *p = list->head;

    for(int i = 0; i < N; i++){
        p = p->next;
        fwrite(&p->data, sizeof(Data),1, fp);
    }
    fclose(fp);
    #endif
    
    LinkList *list2 = LinkListInit();
    FILE *fpp;
    Data data_buf;
    fpp = fopen("./demo.txt","rb");
    for( int i = 0; i < N; i++){
        fread(&data_buf, sizeof(Data), 1, fpp);
        LinkListCreate(list2, 0, &data_buf);
    }
    fclose(fpp);
    LinkListPrintById(list2, stdout, ALL);
    LinkListPrintById(list2, stdout, NAME);
    #endif
    return 0;
}

