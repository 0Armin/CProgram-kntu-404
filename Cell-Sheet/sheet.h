#ifndef Sheet_h
#define Sheet_h
#include <stddef.h>
#define Max_satr 100
#define Max_soton 100
#define Max_formula_tol 256

typedef enum{
    //نوع خطاها
    Err_NONE,Err_taghsim_sefr,Err_tabe_nashenakhte_formul,Err_erjaa_namotabar_beselol,Err_parantez,Err_damane_tabe,Err_fayl,Err_ghaleb_dade
}CellError;

typedef struct{
    char address[10];
    //آدرس متنی سلول
    double value;
    //مقدار عدد ذخیره شده در سلول
    char formula[Max_formula_tol];
    //رشته فرمول
    CellError error;
    //خطاها
}Cell;

typedef struct{
    int satr;
    int soton;
    Cell cells[Max_satr][Max_soton];
    //ماتریس دو بعدی برای سلول
}Sheet;

//توابع مربوط به ستون ها و آدرس ها
int tabdil_esm_be_andisaddadi(const char* name);
void andisaddadi_be_esm(int andisaddadi, char* buffer);
int barrsiaddress_selol(const char* address);
//مقدار دهی و تغییر سایز
void initSheet(Sheet* sheet,int satr,int soton);
//آماده سازی جدول با ابعاد داده شده
void taghir_size_Sheet(Sheet* sheet,int satr_jadid,int soton_jadid);
//ابعاد جدول رو تغییر میده و سلول جدید مفدار دهی می کند و داده های قبلی حفظ میشوند

//تنظیم و کنترل سلول ها
Cell* getCell(Sheet* sheet,const char* address);
int setCellFormula(Sheet* sheet,const char* address,const char* formula);
int setCellValue(Sheet* sheet,const char* address,double value);

//چاپ
void printSheet(const Sheet* sheet);
// چاپ کامل هر سلول با آدرس و مقدار و فرمول و وضعیت خطا
void printSheet_mahdod(const Sheet* sheet,int maxsatrs,int maxsotons);
//چاپ مقادیر با محدودیت داده شده

//ذخیره و بارگذاری
int saveSheetCSV(const Sheet* sheet,const char* filename);
int loadSheetCSV(Sheet* sheet,const char* filename);

//خطاها
void setCellError(Cell* cell,CellError err);
//تنظیم وضعیت خطا برای یک سلول
void clearCellError(Cell* cell);
//پاک کردن خطا
const char* errorToString(CellError err);
//تبدیل نوع خطا به متن

//صحت سنجی ورودی ها
int isvalidnumber(const char*s);
int sanitize_Formula(const char* formula);
#endif
