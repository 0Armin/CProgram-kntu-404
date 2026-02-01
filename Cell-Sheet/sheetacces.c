#include "sheet.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int tabdil_esm_be_andisaddadi(const char* name){
    if (!name || !*name){
         return -1;
         //بررسی میکنه که نام ستون معتبر باشد که غیرتهی و شامل حرف باشد
    }
    int result = 0;
    while (*name && isalpha((unsigned char)*name)) {
        result = result * 26 + (toupper((unsigned char)*name) - 'A' + 1);
        name++;
        /*
با استفاده از یک حلفه هر حرف رو به یک عدد از 1 تا 26 تبدیل میکنه
این اعداد با همدیگر ترکیب می شوند  تا اندیس نهایی  ستون رو به دست بیاره
در اخر هم اندیس رو یک واحد کم میکند  تا اندیس صفر مبنایی به دست بیاد
        */
    }
    return result - 1; /* صفرمبنا */
}
void andisaddadi_be_esm(int andisaddadi, char* buffer){
    // این تابع یک اندیس عددی که از صفر شروع میشه رو به نام ستون تبدیل میکنه
    if (!buffer){ 
        return;
        // اول بررسی برای اینکه که بافر برای ذخیره نام ستون معتبر باشد
    }
    if (andisaddadi < 0) {
         buffer[0] = '\0'; 
         return; 
        }
    int i = 0;
    char temp[10];
    andisaddadi++; /* یک‌مبنا برای محاسبات حروف */
    while ( andisaddadi > 0 && i < (int)sizeof(temp)) {
        /*
        به کمک یک حلفه اندیس رو به صورت مکرر به 26 تقسیم میکنیم و باقیمانده رو به عنوان یک حرف که از آ انگلیسی شروع میشود در بافر ذخیره میکند
        در آخر هم حروف رو به صورت ترتیب معکوس در بافر قرار می دهد تا نام ستون کامل شود
        */
        int rem = (andisaddadi - 1) % 26;
        temp[i++] = (char)('A' + rem);
        andisaddadi = (andisaddadi - 1) / 26;
    }
    for (int j = 0; j < i; j++) buffer[j] = temp[i - j - 1];
    buffer[i] = '\0';
}
int barrsiaddress_selol(const char* address){
    //بررسی اینکه آدرس یک سلول معتبر باشد
    if (!address || !*address){
        return 0;
        // بررسی معتبر بودن آدرس و تهی نبودن
    }
    // کار بعدی بررسی می کند که آدرس شامل حداقل یک حرف برای نام ستون و حداقل یک عدد برای شماره ردیف باشد
    // در آخر هم نام ستون رو به اندیس ستون تبدیل میکنه و شماره ردیف رو به ردیف تبدیل میکنه که اگر هر دو معتبر باشند تابع مفدار 1 رو برمیگرداند
    int i = 0;
    int hasAlpha = 0, hasDigit = 0;
    while (address[i] && isalpha((unsigned char)address[i])) {
         hasAlpha = 1;
          i++;
         }
    if (!hasAlpha){
         return 0;
    }
    int startDigits = i;
    while (address[i] && isdigit((unsigned char)address[i])) { 
        hasDigit = 1;
         i++;
         }
    if (!hasDigit){
     return 0;
    }
    if (address[i] != '\0') {
        return 0;
    }
    /* محدوده‌ها */
    char col[10];
    int len = startDigits < 10 ? startDigits : 9;
    memcpy(col, address, (size_t)len);
    col[len] = '\0';
    int colIndex = tabdil_esm_be_andisaddadi(col);
    int satr = atoi(address + startDigits) - 1;
    return (colIndex >= 0 && colIndex < MAX_COLS && satr >= 0 && satr < Max_satr);
}

Cell* getCell(Sheet* sheet, const char* address) {
    //کار این تابع این هست که یک سلول رو بر اساس آدرس آن برمیگردونه
    if (!sheet || !address){
         return NULL;
    }
    if (!barrsiaddress_selol(address)){
        //بررسی معتبر بودن آدرس
         return NULL;
    }
    //اگر آدرس معتبر بود نام ستون رو به اندیس ستون و شماره ردیف رو به ردیف تبدیل میکند
    //در نهایت هم سلول مربوطه رو برمیگردونه
    char col[10];
    int i = 0;
    while (isalpha((unsigned char)address[i])) {
         col[i] = address[i]; 
         i++;
         }
    col[i] = '\0';
    int satr = atoi(&address[i]) - 1;
    int colIndex =tabdil_esm_be_andisaddadi (col);

    if (satr >= 0 && satr < sheet->satr && colIndex >= 0 && colIndex < sheet->soton) {
        return &sheet->cells[satr][colIndex];
    }
    return NULL;
}

int setCellFormula(Sheet* sheet, const char* address, const char* formula) {
    //فرمول یک سلول رو تنظیم میکنه
    if (!sheet || !address || !formula) {
        return 0;
    }
    Cell* cell = getCell(sheet, address);  //سلول رو به ما میده
    if (!cell){
         return 0;
    }
    // اگر فرمول معتبر باشه فرمول رو در فیلد فرمول سلول ذخیره میکنه
    /*
یک مثالش مثلا آدرس برابر آ1 و فرمول برابر بی1+سی1 باشد ابن تابع فرمول بی1+سی1 رو در آ1 ذخیره میکنه
    */
         strncpy(cell->formula, formula, Max_formula_tol);
    cell->formula[Max_formula_tol - 1] = '\0';
    return 1;
}

int setCellValue(Sheet* sheet, const char* address, double value) {
    if (!sheet || !address) {
        return 0;
    }
    Cell* cell = getCell(sheet, address);
    if (!cell) {
        return 0;
    }
    /*
    اگر سلول معتبر باشد مقدار را در فیلد ولیو سلول ذخیره میکنه
    مثلا اگر ادرس آ1 رو بدی بعد ولیو ش رو 10 بدی  این تابع مقدار 10 رو در آ1 ذخیره میکنه
    */
    cell->value = value;
    return 1;
}
/*
1. buffer (متغیر):

نوع: char* (اشاره‌گر به یک آرایه کاراکتری)
نقش: در تابع indexToColName، buffer یک آرایه کاراکتری است که برای ذخیره نام ستون (مثلاً “A”, “B”, “AA”) استفاده می‌شود. این بافر به عنوان یک فضای موقت برای ساختن نام ستون از اندیس عددی عمل می‌کند.
مثال: در تابع indexToColName، نام ستون به تدریج در buffer ساخته می‌شود و در نهایت buffer حاوی نام ستون کامل خواهد بود.


2. hasDigit (متغیر):

نوع: int (عدد صحیح)
نقش: در تابع isValidCellAddress، hasDigit یک پرچم (flag) است که نشان می‌دهد آیا در آدرس سلول حداقل یک رقم (عدد) وجود دارد یا خیر.
مقدار اولیه: 0 (false)
تغییر: اگر در طول بررسی آدرس، یک رقم پیدا شود، مقدار hasDigit به 1 (true) تغییر می‌کند.


3. hasAlpha (متغیر):

نوع: int (عدد صحیح)
نقش: در تابع isValidCellAddress، hasAlpha یک پرچم (flag) است که نشان می‌دهد آیا در آدرس سلول حداقل یک حرف (حرف الفبا) وجود دارد یا خیر.
مقدار اولیه: 0 (false)
تغییر: اگر در طول بررسی آدرس، یک حرف پیدا شود، مقدار hasAlpha به 1 (true) تغییر می‌کند.


4. isdigit(unsigned char c) (تابع):

کتابخانه: ctype.h
هدف: بررسی می‌کند که آیا یک کاراکتر، یک رقم (عدد) است یا خیر.
ورودی: c: کاراکتری که باید بررسی شود.
خروجی: 1 اگر کاراکتر یک رقم باشد، 0 در غیر این صورت.
مثال: isdigit('5') مقدار 1 را برمی‌گرداند، isdigit('A') مقدار 0 را برمی‌گرداند.



5. isalpha(unsigned char c) (تابع):

کتابخانه: ctype.h
هدف: بررسی می‌کند که آیا یک کاراکتر، یک حرف الفبا است یا خیر.
ورودی: c: کاراکتری که باید بررسی شود.
خروجی: 1 اگر کاراکتر یک حرف الفبا باشد، 0 در غیر این صورت.
مثال: isalpha('A') مقدار 1 را برمی‌گرداند، isalpha('5') مقدار 0 را برمی‌گرداند.


6.توضیح atoi
یک تابع برای تبدیل یک رشته کاراکتری به یک عدد صحیح استفاده میشود
همون تبدیل اسکی میشه
کتابخانه stdlib.h

7.توضیح toupper
یک تابع برای تبدیل یک کاراکتر به بزرگترین حرف بزرگتر معادل آن است
مثلا بی کوچک ورودی بدی بی بزرک میده
کتابخانه ctype.h

*/