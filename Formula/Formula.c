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

    /* بعد از محاسبه، حتماً حافظه لیست را آزاد کن */
    free_list(list);

    /* اگر خواستی می‌توانی بر اساس err پیام چاپ کنی؛ اما خودِ فراخواننده هم می‌تواند این کار را بکند */
    return result;
}