#include "File.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// تابع حذف فاصله
static char* trim(char* str) {
    if (!str) return NULL;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

// تابع شمارش ستون
static int countColumns(const char* line) {
    if (!line || !*line) return 0;
    int count = 1;
    for (int i = 0; line[i]; i++) {
        if (line[i] == ',') count++;
    }
    return count;
}

// تابع اصلی بارگذاری
FileError loadSheetFromFile(Sheet* sheet, const char* filename) {
    if (!sheet || !filename) return FILE_BAD_FORMAT;
    
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("خطا: باز کردن فایل '%s' ناموفق بود.\n", filename);
        return FILE_CANT_OPEN;
    }
    
    printf("در حال خواندن فایل: %s\n", filename);
    
    char buffer[MAX_LINE];
    int totalRows = 0;
    int maxCols = 0;
    
    // فاز ۱: بررسی ابعاد فایل
    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char* trimmed = trim(buffer);
        if (strlen(trimmed) == 0) continue;
        
        int cols = countColumns(buffer);
        if (cols > maxCols) maxCols = cols;
        totalRows++;
    }
    
    if (totalRows == 0 || maxCols == 0) {
        fclose(f);
        printf("خطا: فایل خالی یا بدون داده معتبر.\n");
        return FILE_BAD_FORMAT;
    }
    
    // اعمال محدودیت‌های Max_satr و Max_soton از sheet.h
    if (totalRows > Max_satr) totalRows = Max_satr;
    if (maxCols > Max_soton) maxCols = Max_soton;
    
    printf("ابعاد شناسایی شده: %d سطر، %d ستون\n", totalRows, maxCols);
    
    // فاز ۲: مقداردهی اولیه Sheet با ابعاد جدید
    initSheet(sheet, totalRows, maxCols);
    
    // فاز ۳: بازخوانی فایل و پر کردن داده‌ها
    rewind(f);
    int currentRow = 0;
    
    while (fgets(buffer, sizeof(buffer), f) && currentRow < totalRows) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(trim(buffer)) == 0) continue;
        
        char lineCopy[MAX_LINE];
        strcpy(lineCopy, buffer);
        
        int col = 0;
        char* token = strtok(lineCopy, ",");
        
        while (token && col < maxCols) {
            char* value = trim(token);
            
            // پردازش مقدار سلول
            if (value[0] == '=') {
                // مقدار یک فرمول است
                strncpy(sheet->cells[currentRow][col].formula, value + 1, Max_formula_tol - 1);
                sheet->cells[currentRow][col].formula[Max_formula_tol - 1] = '\0';
            } else if (strlen(value) > 0) {
                // مقدار یک عدد است
                sheet->cells[currentRow][col].value = atof(value);
            }
            // اگر خالی بود، مقدار پیش‌فرض (صفر) باقی می‌ماند
            
            col++;
            token = strtok(NULL, ",");
        }
        currentRow++;
    }
    
    fclose(f);
    printf("بارگذاری با موفقیت انجام شد. (%d سطر پردازش شد)\n", currentRow);
    return FILE_OK;
}

// تابع اصلی ذخیره‌سازی
FileError saveSheetToFile(const Sheet* sheet, const char* filename) {
    if (!sheet || !filename) return FILE_BAD_FORMAT;
    
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("خطا: ایجاد فایل '%s' ناموفق بود.\n", filename);
        return FILE_CANT_OPEN;
    }
    
    printf("در حال ذخیره به فایل: %s\n", filename);
    
    for (int i = 0; i < sheet->satr; i++) {
        for (int j = 0; j < sheet->soton; j++) {
            // چاپ مقدار سلول
            if (sheet->cells[i][j].formula[0] != '\0') {
                fprintf(f, "=%s", sheet->cells[i][j].formula);
            } else {
                fprintf(f, "%.2f", sheet->cells[i][j].value);
            }
            
            // چاپ جداکننده ستون (به جز آخرین ستون)
            if (j < sheet->soton - 1) fprintf(f, ",");
        }
        fprintf(f, "\n"); // پایان سطر
    }
    
    fclose(f);
    printf("ذخیره‌سازی با موفقیت انجام شد.\n");
    return FILE_OK;
}