#include "sheet.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

    //تغییر تعداد سطرها
    
    // اگر تعداد سطرها کم شده سطرهای اضافه آزاد شوند
    if(satr_jadid < satr_ghadimi){
        for(int i = satr_jadid; i < satr_ghadimi; i++){
            free((*sheet).cells[i]);
        }
    }

    Cell** sotoonha_jadid = realloc((*sheet).cells , satr_jadid * sizeof(Cell*));
       if(!sotoonha_jadid){
        return;
    }
    (*sheet).cells = sotoonha_jadid;
    for(int i = 0; i < satr_jadid; i++){
        if(i >= satr_ghadimi){
            (*sheet).cells[i] = malloc(soton_jadid * sizeof(Cell));
            if(!(*sheet).cells[i]){
                return;
            }
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