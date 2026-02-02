#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Cell-Sheet/sheet.h" // استفاده از ساختار واقعی پروژه

// انواع خطاهای ماژول فایل
typedef enum {
    FILE_OK = 0,
    FILE_CANT_OPEN,
    FILE_CANT_READ,
    FILE_CANT_WRITE,
    FILE_BAD_FORMAT,
    FILE_TOO_LARGE
} FileError;

// ثابت‌ها
#define MAX_LINE 1024

// توابع اصلی بارگذاری و ذخیره‌سازی
FileError loadSheetFromFile(Sheet* sheet, const char* filename);
FileError saveSheetToFile(const Sheet* sheet, const char* filename);

// تابع کمکی برای تست
void runFileModuleTest();

#endif