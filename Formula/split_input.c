#include <stdio.h>
#include "split_input.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// در اینحا تابع سی تایپ برای تشخیص عدد،فاصله و حرف به کار رفته
static void meghdardehi(part_list *list){
    list->items = NULL;
    list->current = 0;
    list->maximum = 0;
}
// ابتدا باید قبل از کار با لیستمون مقدار هر قسمت رو بدونیم چی هست
//در اینجا چون برای بار اول لیت رو میسازیم باید یبار این مقدار دهی اولیه رو داشته باشیم
static void add_part(part_list *list, part p){
    if (list->current == list->maximum)
    {
        int new_max;
        if (list->maximum == 0)
        {
            new_max = 8;
        } else {
            new_max = (list->maximum)*2;
        }
        
        list->items = realloc(list->items, new_max*sizeof(part));
        //چون ما بعدا ممکنه نیاز داشته باشیم مقدار حافظه تخصیص داده شده را افزایش بدیم
        //از realloc استفاده کردیم
        list->maximum = new_max;
    }
    list->items[list->current] = p;// قرار دادن در انتهای لیست
    list->current++;
}
// این قسمت مسئول اختصاص دادن حافظه به هر قسمت از لیست ماست

part_list split(char *text){
    part_list list;// یک لیست درست میکنیم
    meghdardehi(&list);//مقدار دهی اولیه انجام میدیم

    int i=0;

    while (text[i] != '\0')//تا زمانی که به انتهای استرینگ ورودی برسد انجام میشود
    {
        if (isspace(text[i]))
        {
            i++;
            continue;
        }
        // اگر فاصله داشتیم رد میکنه

        if (isdigit(text[i]) || text[i] == '.')
        {
            char *end;// یک پوینتر به انتهای عدد
            char *start = &text[i];
            double value = strtod(&text[i],&end);
            //تابع استفاده شده در قسمت بالا یک تابع کمکی هست که استرینگ ورودی رو چک میکنه
            //و کل عدد رو تبدیل به خروجی از نوع دابل میکنه حتی با ممیز
            // قسمتی که پوینتر انتهای عدد رو میدیم درون ان ادرس انتهای عدد رو به ما میده
            part p;
            p.noe = number;
            p.number = value;
            p.text_name = NULL;

            add_part(&list, p);
            i = end - start;
            // در اینجا ادرس انتها را از ادرس ابتدای تکست کم میکند که خونه ای که روش قرار داریم رو برمیگردونه
            //برای مثال اگر عدد ما 
            //text = "34.68"
            //text address = 0x1000
            //end address = 0x1005
            //end - text = 5
            continue;
        }
        
        if (isalpha(text[i]))
        //تشخیص حرف
        {
            int start = i;
            int length;//طول کلمه
            int hasdigit = 0; //برای تشخیص وجود اسم سلول که دارای عدد است
            while (isalpha(text[i]))
            {
                i++;
            }
            while (isdigit(text[i])) //
            {
                i++;
                hasdigit = 1;
            }
            
            length = i-start;
            char *name = malloc(length + 1);
            strncpy(name, &text[start], length);
            // به تعداد طول کلمه حرف ها را در استرینگ کپی میکند
            name[length]= '\0';

            part p;
            if (hasdigit)
            {
                p.noe = cell_ref;
                //p.value = 
            }else{
                p.noe = function;
            }
            p.number = 0;
            p.text_name = name;

            add_part(&list, p);
            continue;

        }
        
        if (strchr("+-*/^", text[i]))
        //این تابع چک میکند که اگر یکی از علامت های موجود در ورودی وجود دارد یا نه
        //اگر وجود داشت true برمیگرداند
        {
            part p;
            p.noe = operator;
            p.number = 0;
            p.text_name = malloc(2);// فقط یک کاراکتر و نال نیاز داریم
            p.text_name[0] = text[i];
            p.text_name[1] = '\0';

            add_part(&list, p);
            i++;
            continue;
        }

        if (text[i] == '(')//پرانتز باز
        {
            part p;
            p.noe = s_parantes;
            p.number = 0;
            p.text_name = NULL;
            add_part(&list, p);
            i++;
            continue;
        }
        
        if (text[i] == ')')//پرانتز بسته
        {
            part p;
            p.noe = e_parantes;
            p.number = 0;
            p.text_name = NULL;
            add_part(&list, p);
            i++;
            continue;
        }

        printf("Invalid character %c ",text[i]); //اگر هیچ کدام از کاراکتر های بالا نبود اررور میده
        i++;
    }

    return list;
    //برگرداندن لیست درست شده
}
