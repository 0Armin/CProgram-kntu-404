
/* evaluator.c
   پیاده‌سازی توابع ریاضی  و گزارش خطای دامنه یا ناشناخته.
   
*/

#include "formula.h"
#include <string.h>
#include <math.h>

// پیام‌های  برای ارورها //
const char* error_message_fa(int errcode)
{
    switch (errcode) {
        case ERR_NONE: return "بدون خطا";
        case ERR_DIV_ZERO: return "خطا: تقسیم بر صفر";
        case ERR_UNKNOWN_FUNCTION: return "خطا: تابع ناشناخته";
        case ERR_INVALID_CELL: return "خطا: ارجاع به سلول نامعتبر";
        case ERR_EMPTY_CELL: return "توجه: سلول خالی (مقدار 0 در نظر گرفته شد)";
        case ERR_PAREN_MISMATCH: return "خطا: پرانتز نامنطبق";
        case ERR_DOMAIN: return "خطا: مقدار خارج از دامنه تابع";
        case ERR_SYNTAX: return "خطا: نامعتبر";
        default: return "خطا: نامشخص";
    }
}

/* اجرای یک تابع ریاضی
   name: نام تابع (مثلاً "sin")
   arg: آرگومان
   err: بر اساس عددش ارور مناسب
*/
double run_function(const char *name, double arg, int *err)
{
    if (err) *err = ERR_NONE;

    if (strcmp(name, "sin") == 0) return sin(arg);
    if (strcmp(name, "cos") == 0) return cos(arg);
    if (strcmp(name, "tan") == 0) return tan(arg);
    if (strcmp(name, "sinh") == 0) return sinh(arg);
    if (strcmp(name, "cosh") == 0) return cosh(arg);

    if (strcmp(name, "sqrt") == 0) {
        if (arg < 0) {
            if (err) *err = ERR_DOMAIN;
            return 0;
        }
        return sqrt(arg);
    }

    if (strcmp(name, "log") == 0 || strcmp(name, "ln") == 0) {
        if (arg <= 0) {
            if (err) *err = ERR_DOMAIN;
            return 0;
        }
        return log(arg);
    }

    if (strcmp(name, "exp") == 0) return exp(arg);
    if (strcmp(name, "abs") == 0) return fabs(arg);

   // اگر اینجا رسیدیم تابع ناشناخته است //
    if (err) *err = ERR_UNKNOWN_FUNCTION;
    return 0;
}