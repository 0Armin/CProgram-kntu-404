
/* evaluator.c
   پیاده‌سازی توابع ریاضی  و گزارش خطای دامنه یا ناشناخته.
   
*/
#include <stdio.h>
#include "formula.h"
#include <string.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923




// ادامه کد...
// پیام‌های  برای ارورها //
const char* error_message_fa(int errcode)
{
    switch (errcode) {
        case ERR_NONE: return "without error";
        case ERR_DIV_ZERO: return "Error: Division by zero";
        case ERR_UNKNOWN_FUNCTION: return "Error: Unknown function";
        case ERR_INVALID_CELL: return "Error: Invalid cell reference";
        case ERR_EMPTY_CELL: return "Note: Empty cell (value 0 was considered)";
        case ERR_PAREN_MISMATCH: return "Error: Incompatible parentheses";
        case ERR_DOMAIN: return "Error: Value outside the function's range";
        case ERR_SYNTAX: return "Error: invalid";
        default: return "Error: Undefined";
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

    if (strcmp(name,"sin") == 0) return sin(arg);
    if (strcmp(name, "cos") == 0) return cos(arg);
    if (strcmp(name, "sinh") == 0) return sinh(arg);
    if (strcmp(name, "cosh") == 0) return cosh(arg);
    if (strcmp(name, "tanh") == 0) return tanh(arg);

    if (strcmp(name, "sqrt") == 0) {
        if (arg < 0) {
            if (err) *err = ERR_DOMAIN;
            return 0;
        }
        return sqrt(arg);}
    

    if (strcmp(name,"tan") == 0) {
    // بررسی دامنه برای tan
    if (fmod(arg, M_PI_2) == 0 && fmod(arg, M_PI) != 0) {  // اگر arg برابر با π/2 یا مضاربی از آن باشد
        if (err) *err = ERR_DOMAIN;  // خطای دامنه بدهد
        return 0;}
    
    return tan(arg);  
}
//کتانژانت را نداریم پس معکوس تانژانت تعریف می کنیم//
if (strcmp(name, "cot") == 0) {
    // بررسی دامنه برای cot (cot = 1/tan)
    if (arg == 0) {  // وقتی arg برابر با 0 باشد
        if (err) *err = ERR_DOMAIN;  // خطای دامنه
        return 0;
    }
    return 1.0 / tan(arg);  // معکوس tan
}   



    if (strcmp(name, "ln") == 0) {
        if (arg <= 0) {
            if (err) *err = ERR_DOMAIN;
            return 0;
        }
        return log(arg);
    }

    if (strcmp(name, "log") == 0) {
        if (arg <= 0) {
            if (err) *err = ERR_DOMAIN;
            return 0;
        }
        return log10(arg);
    }

    if (strcmp(name, "exp") == 0) return exp(arg);
    if (strcmp(name, "abs") == 0) return fabs(arg);

   // اگر اینجا رسیدیم تابع ناشناخته است //
    if (err) *err = ERR_UNKNOWN_FUNCTION;
    return 0;
}
