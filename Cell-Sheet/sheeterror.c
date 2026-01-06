#include "sheet.h"
void setCellError(Cell* cell,CellError err){
    //تنظیم خطا برای یک سلول
    if(!cell){
        return;
    }
    (*cell).error = err;
}
void clearCellError(Cell* cell){
    if(!cell){
        return;
    }
    (*cell).error = Err_NONE;
    //بخش پاک کردن حطا
}
const char* errorToString(CellError err){
    //تبدیل خطا به متن
    switch(err){
        
        case Err_NONE:
        return "خطایی وجود ندارد";
        //خطایی وجود نداره
        
        case Err_taghsim_sefr:
        return "تقسیم بر صفر امکان پذیر نیست";
        //تقسیم بر صفر انجام نمی شود
        
        case Err_tabe_nashenakhte_formul:
        return "تابع ناشناخته در فرمول";
        //وقتی اسم تابعی داده بشه که تو برنامه وجود نداره

        case Err_erjaa_namotabar_beselol:
        return "ارجاع نامعتبر";
        //وقتی که فرمول به سلول ارجاع میشه که فرمول وجود نداره 

        case Err_parantez:
        return "خطای پرانتز";
        //پرانتز ها درست در جای خودش نباشه یعنی درست باز و بسته نشده

        case Err_damane_tabe:
        return "خطای دامنه تابع در ورودی";
        //ورودی یک تابع در محدوده دامنه تابع وجود نداشته باشد

        case Err_file:
        return "خطای فایل";
        //خطاهای مربوط به ذخیره و بارگذاری فایل

        case Err_ghaleb_dade:
        return "خطا در قالب داده";
        //داده ورودی قالب و فرمت درستی نداشته نباشد مثلا بجای عدد رشته نامفهوم وارد بشه

        default:
        return "خطای ناشناخته";
    }
}

