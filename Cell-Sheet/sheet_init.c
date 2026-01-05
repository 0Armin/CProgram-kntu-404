#include "sheet.h"
#include <stdio.h>
#include <string.h>
//تعریف تابعی که مفدار دهی اولیه می کند
//ورودی هاش اشاره گر به جدول اصلی و سطرها و ستون ها
void initSheet(Sheet* sheet,int satr,int soton){
    if(!sheet){
        return;
        //وقتی اشاره گر جدول تهی بود خارج میشه
    }
    if(satr<1){
        satr=1;
        //حداقل یک سطر وجود داره
    }
    if(soton<1){
        soton=1;
        //حداقل یک ستون رو داریم
    }
    if(satr > Max_satr){
        satr = Max_satr;
        //اگر سطر بیشتر از محدوده بود سطر باید محدود شود
    }
    if(soton > Max_soton){
        soton = Max_soton;
                //اگر سطر بیشتر از محدوده بود سطر باید محدود شود
    }
    // این بخش بالا برای این بود ورودی کاربرمون دچار خطا نشود

(*sheet).satr = satr;
(*sheet).soton = soton;
//تعداد سطرها و ستون ها دخیره میشه

//مقداردهی سلول
for(int i =0; i<satr; i++){
    for(int j=0; j<soton; j++){
        Cell* cell= &(*sheet).cells[i][j];   // اشاره گر به سلول فعلی
    (*cell).value = 0.0;  //مقدار داخل سلول صفر
    (*cell).formula[0] = '\0';  //رشته فرمول خالی
    (*cell).error = Err_NONE;   //وضعیت بدون خطا

    //ساخت آدرس برای سلول
    char esm[10]; //یک رشته برای نام ستون
    andisaddadi_be_esm(j,esm);
    snprintf((*cell).address,sizeof((*cell).address),"%s%d",esm, i+1); //ساخت رشته آدرس سلول که شامل اسم ستون و شماره سطر
    }
}
}
//بخش کد این قسمت برای این هستش که جدول ساخته و سلول ها تشکیل شود و همه جاها خالی باشد مثل فرمول 