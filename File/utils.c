#include "File.h"

/* Trim leading and trailing whitespace */
char* trimSpace(char *s){
    if(!s) return NULL;
    while(isspace((unsigned char)*s)) s++;
    if(!*s) return s;
    char *e=s+strlen(s)-1;
    while(e>s && isspace((unsigned char)*e)) e--;
    e[1]='\0';
    return s;
}

int countCSVColumns(const char *line){
    if(!line||!*line) return 0;
    int c=1; while(*line) if(*line++==',') c++;
    return c;
}

/* Set cell content based on token */
int parseValue(const char* t, Sheet* sh, int r, int c){
    if(!t||!sh) return -1;
    Cell* cell=getCellByIndex(sh,r,c);
    if(!cell) return -1;

    t=trimSpace((char*)t);

    if(!*t || !strcasecmp(t,"null")){
        cell->type=CELL_EMPTY; cell->value=0; cell->formula[0]=0; cell->error=Err_NONE;
        return 0;
    }

    if(t[0]=='='){
        strncpy(cell->formula,t+1,MAX_FORMULA-1);
        cell->formula[MAX_FORMULA-1]=0;
        cell->type=CELL_FORMULA; cell->error=Err_NONE;
        return 0;
    }

    char *e; double v=strtod(t,&e);
    if(e!=t && (!*e || isspace((unsigned char)*e))){
        cell->value=v; cell->type=CELL_NUMBER; cell->formula[0]=0; cell->error=Err_NONE;
        return 0;
    }

    cell->type=CELL_TEXT; cell->value=0; cell->error=Err_NONE;
    return -1;
}

void makeAddress(int r,int c,char* buf,size_t sz){
    if(!buf||sz<4) return;
    char t[10]; int i=0;
    do{ t[i++]='A'+(c%26); c=c/26-1; }while(c>=0);
    for(int j=0;j<i;j++) buf[j]=t[i-j-1];
    snprintf(buf+i,sz-i,"%d",r+1);
}

char* readWholeFile(const char* fn){
    if(!fn) return NULL;
    FILE* f=fopen(fn,"rb"); if(!f) return NULL;
    fseek(f,0,SEEK_END); long n=ftell(f); rewind(f);
    char* b=malloc(n+1); if(!b){ fclose(f); return NULL; }
    fread(b,1,n,f); b[n]=0; fclose(f);
    return b;
}

int checkAddress(const char* a){
    if(!a||!isalpha(*a)) return 0;
    int i=0; while(isalpha(a[i])) i++;
    if(!isdigit(a[i])) return 0;
    while(isdigit(a[i])) i++;
    return a[i]=='\0';
}

int addressToIndex(const char* a,int* r,int* c){
    if(!checkAddress(a)||!r||!c) return -1;
    int i=0; *c=0;
    while(isalpha(a[i])) *c=*c*26+(toupper(a[i++])-'A'+1);
    *c-=1; *r=atoi(a+i)-1;
    return 0;
}
