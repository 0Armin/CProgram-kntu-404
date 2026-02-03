
#ifndef FORMULA_H
#define FORMULA_H

#include "split_input.h"
#include"sheet.h"

// کدهای خطا //
#define ERR_NONE 20//بدون ارور//
#define ERR_DIV_ZERO 21 //خطای تقسیم بر صفر//
#define ERR_UNKNOWN_FUNCTION 22//تابع ریاضی نامعتبر//
#define ERR_INVALID_CELL 23 //ارجاع به سلول نامعتبر //
#define ERR_EMPTY_CELL 24// سلول مقدار ندارد//
#define ERR_PAREN_MISMATCH 25// عدم تطابق پرانتزها (پرانتز باز و بسته برابر نیست)//
#define ERR_DOMAIN 26// خطای دامنه تابع (مثلاً ریشه عدد منفی یا لگاریتم عدد نامعتبر)//
#define ERR_SYNTAX 27// خطای نحوی در عبارت ورودی//

double formula(char *input, Sheet *sheet);
//ارور هندلینگ در بخش اجرای توابع ریاضی انجام شده و تمام پاسخ به فارسی دارند و ارور نمیده//
const char* error_message_fa(int errcode);

// اجرای توابع ریاضی (evaluator) //

double run_function(const char *name, double arg, int *err);

/* تابع اصلی که لیست توکن را می‌گیرد و مقدار نهایی را برمی‌گرداند
 - list: split لیست تولید شده توسط 

- sheet: void* گذاشته‌ام تا اگر بعدا بخواهید  بدهید، پشتیبانی باشد
منظورم ارجاع سلولی
- err: خروجی کد خطا (ERR_NONE = بدون خطا)

*/
double parse_and_calculate(part_list list, void *sheet, int *err);


#endif