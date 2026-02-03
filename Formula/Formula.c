#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "split_input.h"
#include "formula.h"
#include "sheet.h"
//#include "calculate.h"

//void free_list(part_list list);//بعد از انجام محاسبه حافظه را آزاد میکند

double formula(char *input, Sheet *sheet){
    int err = ERR_NONE;
    part_list list = split(input);//تبدیل استرینگ به چیزی که میتوان با ان کار کرد

    double result = parse_and_calculate(list, &sheet,&err);//محاسبه

    //free_list(list);//ازادسازی حافظه


    
    return result;//برگرداندن مقدار محاسبه شده
}