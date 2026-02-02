#include "file.h"

// حذف فضای خالی از ابتدا و انتهای رشته
char* trimSpace(char* str) {
    if (!str) {
        return NULL;
    }
    
    // حذف فضای خالی از ابتدا
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    // اگر کل رشته فضای خالی بود
    if (*str == '\0') {
        return str;
    }
    
    // حذف فضای خالی از انتها
    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    
    // پایان رشته جدید
    *(end + 1) = '\0';
    
    return str;
}

// پردازش مقدار یک سلول
int parseValue(const char* token, Sheet* sheet, int row, int col) {
    if (!token || !sheet) {
        return -1;
    }
    
    // اگر خالی یا NULL
    if (strlen(token) == 0 || 
        strcasecmp(token, "NULL") == 0 || 
        strcasecmp(token, "null") == 0) {
        Cell* cell = getCell(sheet, row, col);
        if (cell) {
            cell->value = 0.0;
            cell->type = 0;
            cell->formula[0] = '\0';
            cell->error = 0;
        }
        return 0;
    }
    
    // اگر فرمول است (با = شروع می‌شود)
    if (token[0] == '=') {
        Cell* cell = getCell(sheet, row, col);
        if (cell) {
            // کپی فرمول (بدون علامت =)
            const char* formulaStart = token + 1;
            strncpy(cell->formula, formulaStart, MAX_FORMULA - 1);
            cell->formula[MAX_FORMULA - 1] = '\0';
            cell->type = 2; // نوع فرمول
            cell->error = 0;
        }
        return 0;
    }
    
    // اگر عدد است
    char* endPtr;
    double value = strtod(token, &endPtr);
    
    // بررسی موفقیت تبدیل
    if (endPtr != token && (*endPtr == '\0' || isspace((unsigned char)*endPtr))) {
        Cell* cell = getCell(sheet, row, col);
        if (cell) {
            cell->value = value;
            cell->type = 1; // نوع عدد
            cell->formula[0] = '\0';
            cell->error = 0;
        }
        return 0;
    }
    
    // اگر رشته متنی است (برای نسخه‌های آینده)
    Cell* cell = getCell(sheet, row, col);
    if (cell) {
        cell->value = 0.0;
        cell->type = 3; // نوع متن
        // در نسخه ساده از متن پشتیبانی نمی‌کنیم
        cell->error = 0;
    }
    
    return -1; // نوع نامعتبر
}

// ساخت آدرس سلول (مثلاً A1, B2, AA10)
void makeAddress(int row, int col, char* buffer, size_t size) {
    if (!buffer || size < 10) {
        return;
    }
    
    // تبدیل ستون به حروف
    char colLetters[10];
    int tempCol = col;
    int index = 0;
    
    do {
        colLetters[index] = 'A' + (tempCol % 26);
        tempCol = tempCol / 26 - 1;
        index++;
    } while (tempCol >= 0);
    
    // معکوس کردن رشته حروف
    for (int i = 0; i < index / 2; i++) {
        char temp = colLetters[i];
        colLetters[i] = colLetters[index - i - 1];
        colLetters[index - i - 1] = temp;
    }
    colLetters[index] = '\0';
    
    // ترکیب با شماره سطر
    snprintf(buffer, size, "%s%d", colLetters, row + 1);
}

// خواندن کل فایل به صورت رشته
char* readWholeFile(const char* filename) {
    if (!filename) {
        return NULL;
    }
    
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }
    
    // پیدا کردن اندازه فایل
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    
    if (fileSize <= 0) {
        fclose(file);
        return NULL;
    }
    
    // اختصاص حافظه
    char* buffer = (char*)malloc(fileSize + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }
    
    // خواندن فایل
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    buffer[bytesRead] = '\0';
    
    fclose(file);
    return buffer;
}

// بررسی صحت آدرس سلول
int checkAddress(const char* address) {
    if (!address || strlen(address) < 2) {
        return 0;
    }
    
    int i = 0;
    int hasLetter = 0, hasDigit = 0;
    
    // بخش حروف
    while (address[i] && isalpha((unsigned char)address[i])) {
        hasLetter = 1;
        i++;
    }
    
    if (!hasLetter) {
        return 0;
    }
    
    // بخش اعداد
    while (address[i] && isdigit((unsigned char)address[i])) {
        hasDigit = 1;
        i++;
    }
    
    if (!hasDigit) {
        return 0;
    }
    
    // باید به پایان رشته رسیده باشیم
    return (address[i] == '\0');
}

// تبدیل آدرس به اندیس‌های سطر و ستون
int addressToIndex(const char* address, int* row, int* col) {
    if (!address || !row || !col) {
        return -1;
    }
    
    if (!checkAddress(address)) {
        return -1;
    }
    
    // جدا کردن حروف و اعداد
    int i = 0;
    char colStr[10] = "";
    char rowStr[10] = "";
    
    // استخراج حروف ستون
    int colIndex = 0;
    while (address[i] && isalpha((unsigned char)address[i])) {
        colStr[colIndex++] = address[i];
        i++;
    }
    colStr[colIndex] = '\0';
    
    // استخراج اعداد سطر
    int rowIndex = 0;
    while (address[i] && isdigit((unsigned char)address[i])) {
        rowStr[rowIndex++] = address[i];
        i++;
    }
    rowStr[rowIndex] = '\0';
    
    // تبدیل حروف ستون به عدد
    *col = 0;
    for (int j = 0; j < colIndex; j++) {
        *col = *col * 26 + (toupper(colStr[j]) - 'A' + 1);
    }
    *col -= 1; // تبدیل به اندیس صفر-محور
    
    // تبدیل رشته سطر به عدد
    *row = atoi(rowStr) - 1; // تبدیل به اندیس صفر-محور
    
    return 0;
}