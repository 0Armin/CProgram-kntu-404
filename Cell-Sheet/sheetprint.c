#include "sheet.h"
#include <stdio.h>
void printSheet(const Sheet* sheet){
    if(!sheet){
        return;
        //وقتی اشاره گر جدول تهی بود خارج میشه
    }
    for(int i=0; i<(*sheet).satr; i++){
        for(int j=0; j<(*sheet).soton; j++){
            const Cell* cell = &(*sheet).cells[i][j];
            printf("%s: %.4f[%s] (%s)\t", (*cell).address, (*cell).value, (*cell).formula,errorTostring((*cell).error));
        }
        printf("\n");
    }
}
void printSheet_mahdod(const Sheet* sheet,int maxsatr,int maxsoton){
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
for(int i=0; i<maxsatr; i++){
    for(int j=0; j<maxsoton; j++){
        const Cell* cell = &(*sheet).cells[i][j];
        printf("%.4f\t", (*cell).value);
    }
    printf("\n");
}
}
