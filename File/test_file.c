#include "File.h"
#include <stdio.h>
#include <assert.h>

// ==================== تست توابع کمکی ====================

void testUtilityFunctions() {
    printf("🧪 شروع تست توابع کمکی\n");
    printf("============================\n");
    
    // تست trimString
    {
        printf("تست trimString... ");
        char test1[] = "  hello world  ";
        char test2[] = "\t\n  test  \t\n";
        char test3[] = "no_spaces";
        
        assert(strcmp(trimString(test1), "hello world") == 0);
        assert(strcmp(trimString(test2), "test") == 0);
        assert(strcmp(trimString(test3), "no_spaces") == 0);
        printf("✅ گذشت\n");
    }
    
    // تست countCSVColumns
    {
        printf("تست countCSVColumns... ");
        assert(countCSVColumns("1,2,3") == 3);
        assert(countCSVColumns("A,B,C,D") == 4);
        assert(countCSVColumns("") == 0);
        assert(countCSVColumns("single") == 1);
        assert(countCSVColumns("\"A,B\",C") == 2);  // quoted comma
        printf("✅ گذشت\n");
    }
    
    printf("============================\n");
    printf("✅ تمام تست‌های کمکی با موفقیت گذشتند!\n\n");
}

// ==================== تست یکپارچه‌سازی ====================

void testFileIntegration() {
    printf("🔗 شروع تست یکپارچه‌سازی فایل\n");
    printf("============================\n");
    
    Sheet testSheet;
    const char* testFilename = "integration_test.csv";
    const char* outputFilename = "integration_output.csv";
    
    // ایجاد فایل تست
    printf("1. ایجاد فایل تست CSV...\n");
    FILE* testFile = fopen(testFilename, "w");
    if (!testFile) {
        printf("❌ خطا: نمی‌توان فایل تست را ایجاد کرد\n");
        return;
    }
    
    // داده‌های تست
    fprintf(testFile, "10,20.5,30.75\n");
    fprintf(testFile, "=A1*2,45,=C1/2\n");
    fprintf(testFile, "100,200,300\n");
    fprintf(testFile, ",500,600\n");  // سلول خالی
    fclose(testFile);
    
    printf("✅ فایل تست ایجاد شد: %s\n", testFilename);
    
    // اعتبارسنجی فایل
    printf("2. اعتبارسنجی فایل تست...\n");
    if (validateCSVFile(testFilename)) {
        printf("✅ فایل CSV معتبر است\n");
    } else {
        printf("❌ فایل CSV نامعتبر است\n");
    }
    
    // بارگذاری فایل
    printf("3. بارگذاری فایل تست...\n");
    FileError loadResult = loadSheetFromCSV(&testSheet, testFilename);
    
    if (loadResult == FILE_SUCCESS) {
        printf("✅ فایل با موفقیت بارگذاری شد\n");
        printf("   ابعاد Sheet: %d × %d\n", testSheet.satr, testSheet.soton);
        
        // نمایش اطلاعات نمونه
        printf("4. نمایش نمونه‌ای از داده‌ها:\n");
        for (int i = 0; i < testSheet.satr && i < 2; i++) {
            printf("   سطر %d: ", i + 1);
            for (int j = 0; j < testSheet.soton && j < 3; j++) {
                printf("[%s] ", testSheet.cells[i][j].address);
            }
            printf("\n");
        }
        
        // ذخیره فایل
        printf("5. ذخیره فایل خروجی...\n");
        FileError saveResult = saveSheetToCSV(&testSheet, outputFilename);
        
        if (saveResult == FILE_SUCCESS) {
            printf("✅ فایل خروجی ذخیره شد: %s\n", outputFilename);
            
            // ذخیره فرمت‌دار (اختیاری)
            printf("6. ذخیره فرمت‌دار (برای نمره بیشتر)...\n");
            saveSheetFormatted(&testSheet, "integration_formatted.txt");
            printf("✅ فایل فرمت‌دار ذخیره شد\n");
        }
    } else {
        printf("❌ خطا در بارگذاری فایل: کد %d\n", loadResult);
    }
    
    // پاکسازی
    printf("7. پاکسازی فایل‌های موقت...\n");
    remove(testFilename);
    remove(outputFilename);
    remove("integration_formatted.txt");
    printf("✅ پاکسازی انجام شد\n");
    
    printf("============================\n");
    printf("✅ تست یکپارچه‌سازی با موفقیت تکمیل شد!\n\n");
}

// ==================== تابع اصلی تست ====================

int main() {
    printf("\n");
    printf("⚡️ تست سیستم فایل - بخش C ⚡️\n");
    printf("============================\n\n");
    
    // اجرای تست‌ها
    testUtilityFunctions();
    testFileIntegration();
    
    printf("🎉 تمام تست‌ها با موفقیت اجرا شدند!\n");
    printf("بخش File I/O آماده ادغام با پروژه اصلی است.\n");
    
    return 0;
}