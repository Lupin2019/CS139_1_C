/*
 * @Author: mathis 
 * @Date: 2021-12-21 00:55:58 
 * @Last Modified by: mathis
 * @Last Modified time: 2021-12-21 01:12:03
 */

#ifndef _ANSWER1
#define _ANSWER1

// word link list
typedef struct _word {
    int length;
    struct _word* next;
} word;

// realize by getchar()
// easy for input but need some strategy for splitting words and counting
void count();

#endif