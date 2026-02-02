#include "file.h"

// بررسی صحت کل فایل CSV
int isValidFile(const char* filename) {
    if (!filename) {
        return 0;
    }
    
    // اول بررسی کنیم فایل وجود دارد یا نه
    FILE* file = fopen(filename, "r");
    if (!file) {
        return 0;
    }
    
    char line[MAX_LINE];
    int firstLineCols = -1;
    int lineCount = 0;
    int isValid = 1;
    
    while (fgets(line, sizeof(line), file) && isValid) {
        // حذف newline
        line[strcspn(line, "\n")] = '\0';
        line[strcspn(line, "\r")] = '\0';
        
        // نادیده گرفتن خطوط خالی
        char* trimmed = trimSpace(line);
        if (strlen(trimmed) == 0) {
            continue;
        }
        
        // بررسی سینتکس خط
        if (!isValidLine(line)) {
            isValid = 0;
            break;
        }
        
        // شمارش ستون‌ها
        int currentCols = countColsInLine(line);
        
        if (firstLineCols == -1) {
            // اولین خط غیرخالی
            firstLineCols = currentCols;
        } else if (currentCols != firstLineCols) {
            // تعداد ستون‌ها با خط اول فرق دارد
            isValid = 0;
            break;
        }
        
        lineCount++;
    }
    
    fclose(file);
    
    // فایل باید حداقل یک خط داده داشته باشد
    return (isValid && lineCount > 0);
}

// بررسی صحت یک خط CSV
int isValidLine(const char* line) {
    if (!line) {
        return 0;
    }
    
    int quoteCount = 0;
    int length = strlen(line);
    
    // شمارش کوتیشن‌ها
    for (int i = 0; i < length; i++) {
        if (line[i] == '"') {
            quoteCount++;
        }
    }
    
    // تعداد کوتیشن‌ها باید زوج باشد
    if (quoteCount % 2 != 0) {
        return 0;
    }
    
    // بررسی کاراکترهای غیرمجاز
    for (int i = 0; i < length; i++) {
        unsigned char c = (unsigned char)line[i];
        
        // کاراکترهای مجاز: قابل چاپ، تب، کاراکترهای کنترل خط
        if (!isprint(c) && c != '\t' && c != '\r' && c != '\n') {
            return 0;
        }
    }
    
    // بررسی quoteهای تو در تو
    int insideQuotes = 0;
    for (int i = 0; i < length; i++) {
        if (line[i] == '"') {
            // اگر کوتیشن داخل رشته نیست یا escape شده
            if (i == 0 || line[i-1] != '\\') {
                insideQuotes = !insideQuotes;
            }
        } else if (line[i] == ',' && !insideQuotes) {
            // کاما خارج از کوتیشن - مشکلی ندارد
            continue;
        }
    }
    
    // باید خارج از کوتیشن باشیم
    return (insideQuotes == 0);
}

// تشخیص فرمت فایل (CSV ساده یا با فرمول)
int detectFileFormat(const char* filename) {
    if (!filename) {
        return 0;
    }
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        return 0;
    }
    
    char line[MAX_LINE];
    int hasFormulas = 0;
    int hasNumbers = 0;
    
    // فقط 5 خط اول را چک کنیم
    for (int i = 0; i < 5 && fgets(line, sizeof(line), file); i++) {
        line[strcspn(line, "\n")] = '\0';
        
        // بررسی اگر خط فرمول دارد
        char* token;
        char lineCopy[MAX_LINE];
        strcpy(lineCopy, line);
        
        token = strtok(lineCopy, ",");
        while (token != NULL) {
            char* clean = trimSpace(token);
            
            if (strlen(clean) > 0) {
                if (clean[0] == '=') {
                    hasFormulas = 1;
                } else if (isdigit(clean[0]) || 
                          (clean[0] == '-' && isdigit(clean[1]))) {
                    hasNumbers = 1;
                }
            }
            
            token = strtok(NULL, ",");
        }
    }
    
    fclose(file);
    
    if (hasFormulas) {
        return 2; // فایل با فرمول
    } else if (hasNumbers) {
        return 1; // فایل عددی ساده
    } else {
        return 0; // فرمت نامعلوم
    }
}