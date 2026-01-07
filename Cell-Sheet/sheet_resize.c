#include "sheet.h"
#include <stdio.h>
#include <string.h>
void taghir_size_Sheet(Sheet* sheet,int satr_jadid,int soton_jadid){
    if(!sheet){
        return;
        //وقتی اشاره گر جدول تهی بود خارج میشه
    }
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

    // برای این هست که بفهمیم از کجا سلول های جدید رو بخوایم مقدار دهی انجام بدیم
    int satr_ghadimi= (*sheet).satr;
    int soton_ghadimi = (*sheet).soton;

    // مقدار دهی سطرهای جدید
    for(int i= satr_ghadimi; i< satr_jadid; i++){
        for(int j=0; j< soton_jadid; j++){
            Cell* cell = &(*sheet).cells[i][j];
            (*cell).value = 0.0;
            (*cell).formula[0]= '\0';
            (*cell).error = Err_NONE;
           char esm[10]; //یک رشته برای نام ستون
         andisaddadi_be_esm(j,esm);
         snprintf((*cell).address,sizeof((*cell).address),"%s%d",esm, i+1); //ساخت رشته آدرس سلول که شامل اسم ستون و شماره سطر
        }
    }

    // حالا مقداردهی ستون های جدید در سطرهای قدیمی
    //در واقع این بخش ستون های جدید رو در سطر های قبلی مقداردهی میکنه
      for(int i=0; i< satr_ghadimi; i++){
        for(int j= soton_ghadimi; j< soton_jadid; j++){
            Cell* cell = &(*sheet).cells[i][j];
            (*cell).value = 0.0;
            (*cell).formula[0]= '\0';
            (*cell).error = Err_NONE;
           char esm[10]; //یک رشته برای نام ستون
         andisaddadi_be_esm(j,esm);
         snprintf((*cell).address,sizeof((*cell).address),"%s%d",esm, i+1); //ساخت رشته آدرس سلول که شامل اسم ستون و شماره سطر
       // این کد آدرس کامل سلول رو درست می کنه و داخل address ذخیره میکنه
        }
    }
// با ترکیب کلی اینا جدول بزرگتر میشه
    // در اینحا هم که ابعاد جدید ثبت می شوند
    (*sheet).satr= satr_jadid;
    (*sheet).soton = soton_jadid;
}