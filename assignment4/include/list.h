/*
 * @Author: Mathis
 * @Date: 2021-12-23 00:12:56
 * @LastEditTime: 2021-12-26 17:28:49
 * @Description: file content
 * @FilePath: /assignment4/include/list.h
 */

#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    OK = 1,
    ERROR = 0,
} status;

typedef enum{
    ALL = 0,
    NAME = 1,
    AGE = 2,
    CLASS = 3,
    MID_TERM_SCORE = 4,
    HOMEWORK_SCORE = 5,
    FINAL_SCORE = 6
    
} item_id;

status ListRead();
typedef unsigned short int Number;
typedef char String;

typedef struct _Data{
    String name[30];
    Number age;
    String class_8[9];
    Number mid_term_score;
    Number homework_score;
    Number final_score;
} Data;

typedef struct Node{
    Data data;
    struct Node *next;
} Node;

typedef struct _LinkList{
    Node *head;
    Node *tail;
    size_t len;
} LinkList;


// operations on a singly linked list

/**
 * @description: init a LinkList
 * @param void
 * @return a LinkList pointer
 */

LinkList* LinkListInit();


/**
 * @description: Read
 * @param list + pos + a data pointer catching output
 * pos: 0 means the last one
 * pos: 1 the first
 * @return status
 */
status LinkListRead(LinkList *list, size_t pos, Data* data);


/**
 * @description: Create a new node with position
 * @param list, pos (0 means the last one), Data* data
 * @return status
 */
status LinkListCreate(LinkList *list, size_t pos, Data* data);


/**
 * @description: 
 * @param {LinkList} *list
 * @param {size_t} pos
 * @return {*}
 */
status LinkListDelete(LinkList *list, size_t pos);


/**
 * @description: 
 * @param {LinkList} *list
 * @param {size_t} pos
 * @param {Data} *data
 * @return {*}
 */
status LinkListUpdate(LinkList *list, size_t pos, Data *data);


/**
 * @description: clear all nodes except the head node;
 * @param {LinkList} *list
 * @return {*}
 */
status LinkListClear(LinkList *list);


/**
 * @description: 
 * @param {LinkList} *list
 * @return {*}
 */
status LinkListDeinit(LinkList *list);


/**
 * @description: 
 * @param {LinkList} *list
 * @param {FILE*} fp
 * 
 * @return {*}
 */
status LinkListPrint(LinkList *list, FILE* fp);



/**
 * @description: Clone
 * @param {LinkList} *list
 * @return {*}
 */
LinkList* LinkListClone(LinkList *list);



/**
 * @description: 
 * @param {LinkList} *list
 * @param {FILE*} fp
 * @param item_id
 * @return {*}
 */
status LinkListPrintById(LinkList *list, FILE* fp, item_id);



/**
 * @description: 
 * @param {LinkList*} list
 * @return {*}
 */
void LinkListSortByScore(LinkList* list);


/**
 * @description: 
 * @param {*}
 * @return {*}
 */
Data DataInitKeyboard();


/**
 * @description: 
 * @param {LinkList*} list
 * @return {*}
 */
void LinkListReverse(LinkList* list);


/**
 * @description: 
 * @param {LinkList} *list
 * @param {char*} path
 * @param {size_t} N
 * @return {*}
 */
void load_from_data_dir(LinkList *list, char* path, size_t N);

#endif
