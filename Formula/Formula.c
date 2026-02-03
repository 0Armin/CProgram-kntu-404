#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "split_input.h"

//void free_list(part_list list);//بعد از انجام محاسبه حافظه را آزاد میکند

//double formula(char *input, Sheet *sheet){
   // int err = ERR_NONE;
    //part_list list = split(input);//تبدیل استرینگ به چیزی که میتوان با ان کار کرد

    //double result = parse_and_calculate(list, &sheet,&err);//محاسبه

    //free_list(list);//ازادسازی حافظه


    
  //  return result;//برگرداندن مقدار محاسبه شده
//}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "split_input.h"
#include "formula.h"
#include "sheet.h"

/* تابع آزادکننده */
void free_list(part_list list)
{
    if (list.items == NULL) return;

    for (int i = 0; i < list.current; i++) {
        if (list.items[i].text_name != NULL) {
            free(list.items[i].text_name);
            list.items[i].text_name = NULL;
        }
    }
    free(list.items);
}

/* تابع اصلی که فرمول را گرفته و مقدار را برمی‌گرداند */
double formula(char *input, Sheet *sheet)
{
    int err = ERR_NONE;

    /* تولید لیست توکن‌ها */
    part_list list = split(input);

    // محاسبه://
   
    double result = parse_and_calculate(list, (void*)sheet, &err);

    switch (err)
    {
    case ERR_DIV_ZERO:
        printf("error taghsim bar sefr\n");
        break;
    case ERR_UNKNOWN_FUNCTION:
        printf("error function namoshakhaser\n");
        break;
    case ERR_INVALID_CELL:
        printf("error selol namotabar\n");
        break;
    case ERR_EMPTY_CELL:
        printf("error selol khali\n");
        break;
    case ERR_PAREN_MISMATCH:
        printf("error parantes\n");
        break;
    case ERR_DOMAIN:
        printf("error damane\n");
        break;
    case ERR_SYNTAX:
        printf("error syntax\n");
        break;
    case ERR_EMPTY_INPUT:
        printf("error vorody khali\n");
        break;
    default:
        break;
    }
    /* بعد از محاسبه، حتماً حافظه لیست را آزاد کن */
    free_list(list);

    /* اگر خواستی می‌توانی بر اساس 
    err
    پیام چاپ کنی؛ اما خود فراخواننده هم می‌تواند این کار را بکند */
    return result;
}