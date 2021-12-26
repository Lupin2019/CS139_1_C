/*
 * @Author: mathis 
 * @Date: 2021-12-21 00:56:12 
 * @Last Modified by: mathis
 * @Last Modified time: 2021-12-21 01:14:10
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "answer1.h"


#if 0
/**
 * @description: count the length of a word
 * @param {word*} head
 * @param {int} i
 * @return {*}
 */
int getItem(word* head, int i){
    word *k = head;
    while(i){
        k = k->next;
        i--;
    }
    return k->length;
}
#endif 

void count(){
    word *head = (word*)malloc(sizeof(word));
    head->length = 0; // how many words in total
    head->next = NULL;
    word *tail = head;
    char c; // charactor
    int flag = 1; // ready for a new word or not
    printf("input: ");
    while((c=getchar()) != '\n'){
        // skip , . ! ? ...
        if(ispunct(c)){
            continue;
        }
        if(flag && c != ' '){
            head->length++;
            tail->next = (word*)malloc(sizeof(word));
            tail->next->length = 1;
            tail->next->next = NULL;
            flag = 0;
        }else if(c != ' '){
            tail->next->length++;
        }else if(!flag && c ==' '){
            flag = 1;
            tail = tail->next;
        }
    }

    // output print
    printf("The number of words is %d. ", head->length);
    printf("The lengths of these words are");
    word* current = head;
    for (int i = 0; i < head->length; i++){
        current = current->next;
        printf(" %d",current->length);
    }
    printf(".\n");

    // free
    word* tmp = head;
    while(tmp){
        head = head->next;
        free(tmp);
        tmp = head;
    }
}


int main(){
    count();
    return 0;
}
