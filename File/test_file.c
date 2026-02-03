#ifdef RUN_FILE_TESTS
#include "File.h"
#include <assert.h>
#include <stdio.h>

static void testUtils(){
    char a[]="  hi  ";
    assert(strcmp(trimSpace(a),"hi")==0);
    assert(countCSVColumns("1,2,3")==3);
    printf("Utility tests OK\n");
}

static void testIO(){
    const char *f="t.csv";
    Sheet s; initSheet(&s,3,3);

    FILE *fp=fopen(f,"w");
    fprintf(fp,"10,20,30\n=A1*2,5,6\n7,8,9\n");
    fclose(fp);

    assert(loadSheetFromFile(&s,f)==FILE_OK);
    assert(saveSheetToFile(&s,"out.csv")==FILE_OK);

    remove(f); remove("out.csv");
    printf("I/O tests OK\n");
}

int main(){
    testUtils();
    testIO();
    printf("All File module tests passed\n");
    return 0;
}
#endif
