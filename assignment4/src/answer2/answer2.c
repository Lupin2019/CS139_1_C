/*
 * @Author: Mathis
 * @Date: 2021-12-21 01:20:08
 * @LastEditTime: 2021-12-26 16:05:34
 * @Description: file content
 * @FilePath: /assignment4/src/answer2/answer2.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _date_t{
    int year;
    int month;
    int day;    
} date_t;


/**
 * @description: how many days have been passed since 0000-01-01
 * @param {date_t} *date
 * @return {*}
 */
int zero_days(date_t *date){
    int m_d[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int year = date->year;
    int month = date->month;
    int day = date->day;

    int res = 0;
    // the year 0000 is leap year, this date hass pass the whole year(hypothese)
    res = year / 4 - year / 100 + year / 400 + 1;
    // this date has passed leap day or not
    if((month < 3) && (year % 400 == 0 || (year%100 != 0 && year % 4 == 0))){
        res -= 1;
    }
    res += year * 365 + m_d[month-1] + day;
    return  res;
}


/**
 * @description: ex: "2021-12-12" to struct {year: 2021, month:12, day:12}
 * @param {char*} date_string
 * @return {*}
 */
date_t StrToDate(char* date_string){
    unsigned int year, month, day;
    sscanf(date_string, "%d-%d-%d",&year, &month, &day);
    date_t date = {year, month, day};
    return date;
}


/**
 * @description: difference of days of two dates 
 * @param {date_t*} date
 * @param {date_t*} date2
 * @return {*}
 */
int time_delta(date_t* date, date_t* date2){
    int res = zero_days(date) - zero_days(date2);
    if (res < 0){
        return -res;
    }
    return res;
}


int count_down(date_t input_date){
    date_t target = {2022, 2, 4};
    return time_delta(&target, &input_date);
}


int main(){
    time_t now;
    struct tm *tm_now;
    time(&now);
    tm_now = localtime(&now);
    printf("now: %d-%02d-%02d ",1900+tm_now->tm_year, 1+tm_now->tm_mon, tm_now->tm_mday);
    printf("%d:%02d:%02d\n",tm_now->tm_hour, 1+tm_now->tm_min, tm_now->tm_sec);
    date_t today = {1900+tm_now->tm_year, 1+tm_now->tm_mon, tm_now->tm_mday};
    int a = count_down(today);
    printf("count down: \033[1m %d days \033[0m\n",a);
    return 0;
}
