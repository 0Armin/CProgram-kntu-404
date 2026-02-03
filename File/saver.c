#include "File.h"

FileError saveSheetToFile(const Sheet* sheet, const char* filename){
    if(!sheet||!filename) return FILE_BAD_FORMAT;
    FILE* fp=fopen(filename,"w");
    if(!fp) return FILE_CANT_WRITE;

    for(int i=0;i<sheet->satr;i++){
        for(int j=0;j<sheet->soton;j++){
            Cell *c=&sheet->cells[i][j];
            if(c->type==CELL_FORMULA) fprintf(fp,"=%s",c->formula);
            else fprintf(fp,"%.2f",c->value);
            if(j<sheet->soton-1) fputc(',',fp);
        }
        fputc('\n',fp);
    }
    fclose(fp);
    return FILE_OK;
}
