#include "sheet.h"
#include <stdio.h>
void printSheet(const Sheet* sheet){
    //این تابع کل جدول رو با جزییات ش چاپ میکنه
    if(!sheet){
        return;
        //وقتی اشاره گر جدول تهی بود خارج میشه
    }
    //تو حلفه پایین روی تمام سلول های جدول حرکت میکنه
    for(int i=0; i<(*sheet).satr; i++){
        for(int j=0; j<(*sheet).soton; j++){
            const Cell* cell = &(*sheet).cells[i][j];
            printf("%s: %.4f[%s] (%s)\t", (*cell).address, (*cell).value, (*cell).formula,errorToString((*cell).error));
        }
        printf("\n");
    }
}
void printSheet_mahdod(const Sheet* sheet,int maxsatr,int maxsoton){
    //این تابع یک بخش مشخصی از جدول رو چاپ میکنه
    if(!sheet){
        return;
        //وقتی اشاره گر جدول تهی بود خارج میشه
    }
if( maxsatr > (*sheet).satr){
    maxsatr = (*sheet).satr;
}
if( maxsoton > (*sheet).soton){
    maxsoton = (*sheet).soton
}
//در حلقه پایین روی سطر و ستون ها حرکت میکنه
for(int i=0; i<maxsatr; i++){
    for(int j=0; j<maxsoton; j++){
        const Cell* cell = &(*sheet).cells[i][j];
        printf("%.4f\t", (*cell).value);
    }
    printf("\n");
}
}
