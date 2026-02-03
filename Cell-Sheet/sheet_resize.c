#include "sheet.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//تابع تغییر اندازه جدول
void taghir_size_Sheet(Sheet* sheet,int satr_jadid,int soton_jadid){
    if(!sheet){
        return;
        //وقتی اشاره گر جدول تهی بود خارج میشه
    }
    //بررسی ورودی ها و در صورت نیاز اصلاح شود
     if(satr_jadid<1){
        satr_jadid=1;
        //حداقل یک سطر وجود داره
    }
    if(soton_jadid<1){
        soton_jadid=1;
        //حداقل یک ستون رو داریم
    }
    if(satr_jadid > Max_satr){
        satr_jadid = Max_satr;
        //اگر سطر بیشتر از محدوده بود سطر باید محدود شود
    }
    if(soton_jadid > Max_soton){
        soton_jadid = Max_soton;
                //اگر سطر بیشتر از محدوده بود سطر باید محدود شود
    }
 

    //ذخیره تعداد سطر و ستون قبلی برای مقایسه
    // برای این هست که بفهمیم از کجا سلول های جدید رو بخوایم مقدار دهی انجام بدیم
    int satr_ghadimi= (*sheet).satr;
    int soton_ghadimi = (*sheet).soton;

    //تغییر تعداد سطرها
    
    // اگر تعداد سطرها کم شده سطرهای اضافه آزاد شوند
    if(satr_jadid < satr_ghadimi){
        for(int i = satr_jadid; i < satr_ghadimi; i++){
            //قبل از آزاد کردن بررسی میکنه که آیا سلول داده داره یا نه
            for(int j=0; j< soton_ghadimi; j++){
                Cell* cell = &(*sheet).cells[i][j];
                if((*cell).value != 0.0 || (*cell).formula[0] != '\0'){
                    printf("Hoshdar: selol %s daraye dade bode va hazf shod\n", (*cell).address);
        }
    }
    free((*sheet).cells[i]); //آزاد کردن حافظه سطر
  }
}


//تغییر اندازه آرایه سطرها
    Cell** sotoonha_jadid = realloc((*sheet).cells , satr_jadid * sizeof(Cell*));
       if(!sotoonha_jadid){
        return; //اگر حافظه کافی نبود
    }
    (*sheet).cells = sotoonha_jadid;

    //حرکت روی سطرهای جدید و قدیمی
    for(int i = 0; i < satr_jadid; i++){
        if(i >= satr_ghadimi){

            //ایحاد حافظه برای سطر جدید
            (*sheet).cells[i] = malloc(soton_jadid * sizeof(Cell));
            if(!(*sheet).cells[i]){
                return;
            }

    // مقداردهی سلول های سطر جدید
   for(int j = 0; j < soton_jadid; j++){
                Cell* cell = &(*sheet).cells[i][j];
                (*cell).value = 0.0;
                (*cell).formula[0] = '\0';
                (*cell).error = Err_NONE;
                char esm[10];
                andisaddadi_be_esm(j, esm);
                snprintf((*cell).address, sizeof((*cell).address), "%s%d", esm, i+1);
            }
        }
        else {
            //اگر تعداد ستون ها کم شده بود هشدار برای سلول های حذف شده
            if(soton_jadid < soton_ghadimi){
                for(int j = soton_jadid; j< soton_ghadimi; j++){
                    Cell* cell = &(*sheet).cells[i][j];
                    if((*cell).value != 0.0 || (*cell).formula[0] != '\0'){
                        printf("Hoshdar: selol %s daraye dade bod va hazf shod\n", (*cell).address);
                    }
                }
            }

            // سطر قدیمی  فقط ستون‌ها را تغییر می‌دهیم
            Cell* sotonha_jadid = realloc((*sheet).cells[i], soton_jadid * sizeof(Cell));
            if(!sotonha_jadid){
                return;
            }
            (*sheet).cells[i] = sotonha_jadid;
            
            // مقداردهی ستون‌های جدید
            for(int j = soton_ghadimi; j < soton_jadid; j++){
                Cell* cell = &(*sheet).cells[i][j];
                (*cell).value = 0.0;
                (*cell).formula[0] = '\0';
                (*cell).error = Err_NONE;
                char esm[10];
                andisaddadi_be_esm(j, esm);
                snprintf((*cell).address, sizeof((*cell).address), "%s%d", esm, i+1);
            }
        }
    }
//با ترکیب کلی اینا جدول بزرگتر میشه
//در اینجا هم که ابعاد جدید ثبت می شوند
    (*sheet).satr  = satr_jadid;
    (*sheet).soton = soton_jadid;
}