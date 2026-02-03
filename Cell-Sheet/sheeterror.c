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
        return "Khataei vojod nadarad";
        //خطایی وجود نداره
        
        case Err_taghsim_sefr:
        return "Taghsim bar sefr momken nist";
        //تقسیم بر صفر انجام نمی شود
        
        case Err_tabe_nashenakhte_formul:
        return "Tabe nashnakhte dar formula";
        //وقتی اسم تابعی داده بشه که تو برنامه وجود نداره

        case Err_erjaa_namotabar_beselol:
        return "Erja namotabar";
        //وقتی که فرمول به سلول ارجاع میشه که فرمول وجود نداره 

        case Err_parantez:
        return "Khataei parantez";
        //پرانتز ها درست در جای خودش نباشه یعنی درست باز و بسته نشده

        case Err_damane_tabe:
        return "Khateei damane tabe dar vorodi";
        //ورودی یک تابع در محدوده دامنه تابع وجود نداشته باشد

        case Err_file:
        return "Khataei file";
        //خطاهای مربوط به ذخیره و بارگذاری فایل

        case Err_ghaleb_dade:
        return "Khataei dar ghaleb dade";
        //داده ورودی قالب و فرمت درستی نداشته نباشد مثلا بجای عدد رشته نامفهوم وارد بشه

        default:
        return "Khataei nashenakhte";
    }
}

