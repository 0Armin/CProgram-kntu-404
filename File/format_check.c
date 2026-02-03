#include "File.h"

static void stripNL(char *s){ if(s) s[strcspn(s,"\r\n")]=0; }

int isValidLine(const char *line){
    if(!line) return 0;
    int q=0;
    for(;*line;line++){
        if(*line=='"') q^=1;
        else if(!isprint((unsigned char)*line) && *line!='\t') return 0;
    }
    return q==0;
}

int isValidFile(const char* fn){
    if(!fn) return 0;
    FILE* f=fopen(fn,"r"); if(!f) return 0;

    char line[MAX_LINE]; int cols=-1,rows=0,ok=1;
    while(fgets(line,sizeof(line),f)&&ok){
        stripNL(line);
        char *t=trimSpace(line);
        if(!*t) continue;
        if(!isValidLine(t)){ ok=0; break; }

        int c=countCSVColumns(t);
        if(cols==-1) cols=c;
        else if(c!=cols) ok=0;
        rows++;
    }
    fclose(f);
    return ok && rows>0;
}

int detectFileFormat(const char* fn){
    if(!fn) return 0;
    FILE* f=fopen(fn,"r"); if(!f) return 0;

    char line[MAX_LINE],tmp[MAX_LINE];
    int num=0,frm=0;

    for(int i=0;i<5&&fgets(line,sizeof(line),f);i++){
        strcpy(tmp,line);
        char* tok=strtok(tmp,",");
        while(tok){
            tok=trimSpace(tok);
            if(*tok=='=') frm=1;
            else if(isdigit(*tok)||(*tok=='-'&&isdigit(tok[1]))) num=1;
            tok=strtok(NULL,",");
        }
    }
    fclose(f);
    return frm?2:(num?1:0);
}

int validateCSVFile(const char *fn){
    if(!fn) return 0;
    FILE *f=fopen(fn,"r"); if(!f) return 0;
    char line[MAX_LINE]; int cols=-1,ok=1;
    while(fgets(line,sizeof(line),f)&&ok){
        int c=countCSVColumns(line);
        if(cols==-1) cols=c;
        else if(c!=cols) ok=0;
    }
    fclose(f);
    return ok;
}
