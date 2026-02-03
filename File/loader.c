#include "File.h"

FileError loadSheetFromFile(Sheet* sheet, const char* filename){
    if(!sheet||!filename) return FILE_BAD_FORMAT;
    FILE* fp=fopen(filename,"r");
    if(!fp) return FILE_CANT_OPEN;

    char line[MAX_LINE]; int r=0;
    while(fgets(line,sizeof(line),fp) && r<sheet->satr){
        int c=0; char* tok=strtok(line,",");
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
