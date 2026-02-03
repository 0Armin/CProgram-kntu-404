
/* parser.c
   پارسر  بر اساس خروجی split-input (part_list).
   قواعد:
   1- factor عدد و پرانتز و تابع ریاضی و سلول
   2- term ضرب و تقسیم
   3- expression جمع و تفریق
   4- power توان
همه این قسمت با تابع بازگشتی انجام می شود  
   */

#include "formula.h"
#include <string.h>
#include <stdio.h>
#include "split_input.h"
/* موقیت ایندکس توکن است مثلا 3+5*2pos
این میشه
index   0     1     2     3     4
        [3]   [+]   [5]   [*]   [2]     */
static int pos_token;

/* اعلام توابع داخلی 
اعلان تابع نیاز نیست اگر به ترتیب باشه اما چون نمی‌دانیم اعلام تابع انجام می دهیم .
*/
static double parse_expression(part_list list, void *sheet, int *err);
static double parse_term(part_list list, void *sheet, int *err);
static double parse_factor(part_list list, void *sheet, int *err);

// parse_factor: عدد، پرانتز، تابع یا ارجاع سلولی //
static double parse_factor(part_list list, void *sheet, int *err)
{
    if (pos_token >= list.current) { if (err) *err = ERR_SYNTAX; return 0; }
    /*pos_token
               یعنی: الان روی کدام توکن هستیم
list.current
             یعنی: چند تا توکن داری؟

با شرط بررسی می کنیم آیا توکنی برای باقی مانده یا نه ؟
اگر انجام نشد یعنی  منتظر اتمام توکن هستیم اما چیزی نیست پس خطا را خطای نحوی یا ایندکس می گذاریم.
*/

/*چرا return0
doubleچون تابع باید  برگرداند
اما چون خطا داریم، این مقدار دیگر مهم نیست
فقط برای جلوگیری از کرش است
*/


    part p = list.items[pos_token];
    /*
    list.items = آرایه توکن‌ها
    pos_token =  شماره توکن فعلی که به صورت ایندکس ارایه است
     p = کپی توکن برای بررسی
معنی عبارت :توکنی که هستیم داخلش را بردار و برو برای بررسی که تقدم ریاضی را انجام بده و محاسبه کند
    */

    //اگر عدد بود //
    if (p.noe == number) {
        pos_token++;
        return p.number;
    }

    // اگر پرانتز باز بود //
    if (p.noe == s_parantes) {
        pos_token++; //رد شدن از پرانتز همون‌طور که گفتم موقعیت ایندکس//
        double v = parse_expression(list, sheet, err);//محاسبه بین دو پرانتز//
        if (*err != ERR_NONE) return 0;
        // v=value چک می کنیم به پرانتز بسته رسیدیم اگر رسیدیم مقدار را برگرداند . //
        if (pos_token < list.current && list.items[pos_token].noe == e_parantes) {
            pos_token++; 
            return v;
        } else {
            if (err) *err = ERR_PAREN_MISMATCH;
            return 0;
        }
    }

    // اگر تابع بود//
    if (p.noe == function) {
        char namebuf[64];
        strncpy(namebuf, p.text_name ? p.text_name : "", sizeof(namebuf)-1);
        namebuf[sizeof(namebuf)-1] = '\0';
        pos_token++; 

       
        if (pos_token >= list.current || list.items[pos_token].noe != s_parantes) {
            if (err) *err = ERR_SYNTAX;
            return 0;
        }
        pos_token++; 

        double arg = parse_expression(list, sheet, err);
        if (*err != ERR_NONE) return 0;

        if (pos_token < list.current && list.items[pos_token].noe == e_parantes) {
            pos_token++;
        } else {
            if (err) *err = ERR_PAREN_MISMATCH;
            return 0;
        }

        int ferr = ERR_NONE;
        double fres = run_function(namebuf, arg, &ferr);
        if (ferr != ERR_NONE) {
            if (err) *err = ferr;
            return 0;
        }
        return fres;
    }

    //اگر ارجاع سلولی بود //
    if (p.noe == cell_ref) {

        pos_token++;
        if (err) *err = ERR_EMPTY_CELL;
        return 0;
    }

    // هر چیز دیگر که بود برابر با خطای نحوی//
    if (err) *err = ERR_SYNTAX;
    return 0;
}

// تابع برای پردازش عملگر ^ (توان) 
static double parse_power(part_list list, void *sheet, int *err)
{
    // ابتدا عامل پایه (عدد، پرانتز، تابع و غیره)
    double left = parse_factor(list, sheet, err); 
    if (*err != ERR_NONE) return 0;

    // بررسی وجود عملگر ^ 
    while (pos_token < list.current) {
        part p = list.items[pos_token];
        if (p.noe == operator && strcmp(p.text_name, "^") == 0) {  // وقتی ^ پیدا شد
            pos_token++;  // عبور از ^ (رد می‌شود)
            double right = parse_factor(list, sheet, err);  // عامل سمت راست
            if (*err != ERR_NONE) return 0;
            left = pow(left, right);  // محاسبه توان
        } else {
            break;  // اگر ^ نیست، باید خارج شود
        }
    }

    return left;
}

// ضرب و تقسیم //
static double parse_term(part_list list, void *sheet, int *err)
{
    double left = parse_factor(list, sheet, err);
    if (*err != ERR_NONE) return 0;

    while (pos_token < list.current) {
        part p = list.items[pos_token];
        if (p.noe == operator && (strcmp(p.text_name, "*") == 0 || strcmp(p.text_name, "/") == 0)) {
            char op = p.text_name[0];
            pos_token++;
            double right = parse_factor(list, sheet, err);
            if (*err != ERR_NONE) return 0;
            if (op == '*') left *= right;
            else {
                if (right == 0) { if (err) *err = ERR_DIV_ZERO; return 0; }
                left /= right;
            }
        } else break;
    }
    return left;
}

// جمع و تفریق //
static double parse_expression(part_list list, void *sheet, int *err)
{
    double left = parse_term(list, sheet, err);
    if (*err != ERR_NONE) return 0;

    while (pos_token < list.current) {
        part p = list.items[pos_token];
        if (p.noe == operator && (strcmp(p.text_name, "+") == 0 || strcmp(p.text_name, "-") == 0)) {
            char op = p.text_name[0];
            pos_token++;
            double right = parse_term(list, sheet, err);
            if (*err != ERR_NONE) return 0;
            if (op == '+') left += right;

else left -= right;
        } else break;
    }
    return left;
}

//تابع عمومی: parse_and_calculate //
double parse_and_calculate(part_list list, void *sheet, int *err)
{
    if (err) *err = ERR_NONE;
    pos_token = 0;

    if (list.current == 0) { if (err) *err = ERR_SYNTAX; return 0; }

    //حالت خاص: فقط یک عدد //
    if (list.current == 1 && list.items[0].noe == number) {
        if (err) *err = ERR_NONE;
        return list.items[0].number;
    }

    double res = parse_expression(list, sheet, err);
    if (*err != ERR_NONE) return 0;

    if (pos_token < list.current) { if (err) *err = ERR_SYNTAX; return 0; }

    return res;
}