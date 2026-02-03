#include "File.h"

FileError loadSheetFromFile(Sheet* sheet, const char* filename){
    if(!sheet||!filename) return FILE_BAD_FORMAT;
    FILE* fp=fopen(filename,"r");
    if(!fp) return FILE_CANT_OPEN;

    char line[MAX_LINE];
    int rows=0, cols=0;
    while(fgets(line,sizeof(line),fp)){
        char* t=trimSpace(line);
        if(!*t) continue;
        int c=countCSVColumns(t);
        if(c>cols) cols=c;
        rows++;
    }
    if(rows==0 || cols==0){
        fclose(fp);
        return FILE_BAD_FORMAT;
    }

    taghir_size_Sheet(sheet, rows, cols);

    for(int i=0;i<sheet->satr;i++){
        for(int j=0;j<sheet->soton;j++){
            Cell* cell=&sheet->cells[i][j];
            cell->type=CELL_EMPTY;
            cell->value=0;
            cell->formula[0]=0;
            cell->error=Err_NONE;
        }
    }

    rewind(fp);

    int r=0;
    while(fgets(line,sizeof(line),fp) && r<sheet->satr){
        char* t=trimSpace(line);
        if(!*t) continue;
        int c=0; char* tok=strtok(t,",");
        while(tok && c<sheet->soton){
            tok[strcspn(tok,"\r\n")]=0;
            parseValue(tok,sheet,r,c);
            makeAddress(r,c,sheet->cells[r][c].address,sizeof(sheet->cells[r][c].address));
            tok=strtok(NULL,","); c++;
        }
        r++;
    }
    fclose(fp);
    return FILE_OK;
}
