#include "File.h"
#include <stdio.h>

// ==================== تابع اصلی ذخیره ====================

FileError saveSheetToCSV(const Sheet* sheet, const char* filename) {
    // بررسی پارامترهای ورودی
    if (!sheet || !filename) {
        return FILE_ERROR_MEMORY;
    }
    
    // باز کردن فایل برای نوشتن
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("❌ خطا: نمی‌توان فایل '%s' را برای نوشتن باز کرد.\n", filename);
        return FILE_ERROR_OPEN;
    }
    
    printf("💾 در حال ذخیره فایل: %s\n", filename);
    printf("📊 ابعاد Sheet: %d سطر × %د ستون\n", sheet->satr, sheet->soton);
    
    // ---------- ذخیره هر سلول ----------
    for (int row = 0; row < sheet->satr; row++) {
        for (int col = 0; col < sheet->soton; col++) {
            // دسترسی مستقیم به سلول (طبق ساختار نفر A)
            const Cell* cell = &sheet->cells[row][col];
            
            // تصمیم‌گیری درباره محتوای ذخیره شده
            if (cell->formula[0] != '\0') {
                // سلول دارای فرمول: ذخیره با علامت '='
                fprintf(file, "=%s", cell->formula);
            } else if (cell->value != 0.0) {
                // سلول دارای مقدار عددی: ذخیره با دو رقم اعشار
                fprintf(file, "%.2f", cell->value);
            } else {
                // سلول خالی: ذخیره صفر
                fprintf(file, "0");
            }
            
            // جداکننده بین ستون‌ها (کاما)
            if (col < sheet->soton - 1) {
                fprintf(file, ",");
            }
        }
        
        // پایان هر سطر (به جز سطر آخر)
        if (row < sheet->satr - 1) {
            fprintf(file, "\n");
        }
    }
    
    // بستن فایل
    fclose(file);
    
    printf("✅ فایل با موفقیت ذخیره شد.\n");
    return FILE_SUCCESS;
}

// ==================== تابع ذخیره فرمت‌دار (برای نمره اضافه) ====================

FileError saveSheetFormatted(const Sheet* sheet, const char* filename) {
    if (!sheet || !filename) {
        return FILE_ERROR_MEMORY;
    }
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        return FILE_ERROR_OPEN;
    }
    
    // هدر فایل
    fprintf(file, "===========================================\n");
    fprintf(file, "   خروجی سیستم Excel کوچک - پروژه C\n");
    fprintf(file, "===========================================\n\n");
    
    fprintf(file, "تاریخ تولید: %s\n", __DATE__);
    fprintf(file, "ابعاد جدول: %d سطر × %d ستون\n\n", sheet->satr, sheet->soton);
    
    // هدر ستون‌ها
    fprintf(file, "      ");
    for (int col = 0; col < sheet->soton; col++) {
        char colName[10];
        char address[10];
        
        // ساخت نام ستون
        andisaddadi_be_esm(col, colName);
        snprintf(address, sizeof(address), "%s", colName);
        
        fprintf(file, "%-10s", address);
    }
    fprintf(file, "\n");
    
    // خط جداکننده
    fprintf(file, "      ");
    for (int col = 0; col < sheet->soton; col++) {
        fprintf(file, "----------");
    }
    fprintf(file, "\n");
    
    // داده‌های جدول
    for (int row = 0; row < sheet->satr; row++) {
        // شماره سطر
        fprintf(file, "%-5d ", row + 1);
        
        for (int col = 0; col < sheet->soton; col++) {
            const Cell* cell = &sheet->cells[row][col];
            
            if (cell->formula[0] != '\0') {
                // نمایش فرمول‌ها
                fprintf(file, "%-10s", cell->formula);
            } else if (cell->value != 0.0) {
                // نمایش مقادیر عددی
                fprintf(file, "%-10.2f", cell->value);
            } else {
                // سلول‌های خالی
                fprintf(file, "%-10s", "-");
            }
        }
        fprintf(file, "\n");
    }
    
    // پاورقی
    fprintf(file, "\n===========================================\n");
    fprintf(file, "تعداد سلول‌ها: %d\n", sheet->satr * sheet->soton);
    fprintf(file, "===========================================\n");
    
    fclose(file);
    return FILE_SUCCESS;
}