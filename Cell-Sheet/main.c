#include "sheet.h"
#include <stdio.h>
int main() {
    printf("=== شروع برنامه شبیه‌ساز جدول ===\n\n");
    Sheet sheet;
    // 1) مقداردهی اولیه جدول
    printf("ایجاد جدول 2x2 ...\n");
    initSheet(&sheet, 2, 2);
    printSheet(&sheet);
    printf("\n--------------------------------------\n");
    // 2) مقداردهی به چند سلول
    printf("تنظیم مقدار برای A1 و B1 ...\n");
    setCellValue(&sheet, "A1", 10.5);
    setCellValue(&sheet, "B1", 20.25);
    printf("تنظیم فرمول برای A2 ...\n");
    setCellFormula(&sheet, "A2", "A1+B1");
    printSheet(&sheet);
    printf("\n--------------------------------------\n");
    // 3) تست خطا
    printf("تست خطا: تقسیم بر صفر در B2 ...\n");
    Cell* c = getCell(&sheet, "B2");
    if (c) {
        setCellError(c, Err_taghsim_sefr);
    }
    printSheet(&sheet);
    printf("\n--------------------------------------\n");
    // 4) تغییر اندازه جدول
    printf("تغییر اندازه جدول به 4x3 ...\n");
    taghir_size_Sheet(&sheet, 4, 3);
    printSheet(&sheet);
    printf("\n--------------------------------------\n");
    // 5) چاپ محدود
    printf("چاپ محدود (2x2):\n");
    printSheet_mahdod(&sheet, 2, 2);
    printf("\n--------------------------------------\n");
    // 6) تست آدرس نامعتبر
    printf("تست آدرس نامعتبر: Z100 ...\n");
    Cell* wrong = getCell(&sheet, "Z100");
    if (!wrong) {
        printf("آدرس Z100 نامعتبر است.\n");
    }
    printf("\n--------------------------------------\n");
    printf("=== پایان برنامه ===\n");
    return 0;
}