#include "sheet.h"
#include <stdio.h>
int main() {
    Sheet sheet;
    int init = 0;
    while (1) {
        menu();
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            int satr, soton;
            printf("تعداد سطر: ");
            scanf("%d", &satr);
            printf("تعداد ستون: ");
            scanf("%d", &soton);
            initSheet(&sheet, satr, soton);
            init = 1;  //نقش یک پرچم رو بازی میکنه که متوجه بشیم آیا جدول مقدار دهی انجام شده یا خیر که عدد 1 یعنی حدول آماده استفاده کردن شده است
            printf("جدول مقداردهی شد.\n");
        }
        else if (choice == 2) {
            if (!init) {
                //بررسی اینکه جدول خالی نباشه و اول جدول ساخته شود
                printf("اول جدول را مقداردهی اولیه کنید.\n");
                continue;
            }
            char address[10];
            double value;
            printf("آدرس سلول (مثلاً A1): ");
            scanf("%s", address);
            printf("مقدار عددی: ");
            scanf("%lf", &value);
            if (setCellValue(&sheet, address, value))
                printf("مقدار تنظیم شد.\n");
            else
                printf("خطا: آدرس نامعتبر.\n");
        }
        else if (choice == 3) {
            if (!init) {
                printf("اول جدول را مقداردهی اولیه کنید\n");
                continue;
            }
            char address[10];
            char formula[Max_formula_tol];
            printf("آدرس سلول: ");
            scanf("%s", address);
            printf("فرمول: ");
            scanf("%s", formula);
            if (!sanitize_Formula(formula)) {
                printf("فرمول نامعتبر است.\n");
                continue;
            }
            if (setCellFormula(&sheet, address, formula))
                printf("فرمول تنظیم شد.\n");
            else
                printf("خطا: آدرس نامعتبر.\n");
        }
        else if (choice == 4) {
            if (!init) {
                printf("اول جدول را مقداردهی اولیه کنید.\n");
                continue;
            }
            printSheet(&sheet);
        }
        else if (choice == 5) {
            if (!init) {
                printf("اول جدول را مقداردهی اولیه کنید.\n");
                continue;
            }
            int maxsatr, maxsoton;
            printf("حداکثر سطر: ");
            scanf("%d", &maxsatr);
            printf("حداکثر ستون: ");
            scanf("%d", &maxsoton);
           printSheet_mahdod(&sheet, maxsatr, maxsoton);
        }
        else if (choice == 6) {
            if (!init) {
                printf("اول جدول را مقداردهی اولیه کنید.\n");
                continue;
            }
            int satr_jadid, soton_jadid;
            printf("سطر جدید: ");
            scanf("%d", &satr_jadid);
            printf("ستون جدید: ");
            scanf("%d", &soton_jadid);
            taghir_size_Sheet(&sheet, satr_jadid, soton_jadid);
            printf("اندازه جدول تغییر کرد.\n");
        }
        else if (choice == 7) {
            printf("خروج از برنامه...\n");
            break;
        }
        else {
            printf("گزینه نامعتبر.\n");
        }
    }
    return 0;
}
void menu() {
    printf("\n===== منوی اصلی =====\n");
    printf("1) مقداردهی اولیه جدول\n");
    printf("2) تنظیم مقدار یک سلول\n");
    printf("3) تنظیم فرمول یک سلول\n");
    printf("4) چاپ کامل جدول\n");
    printf("5) چاپ محدود جدول\n");
    printf("6) تغییر اندازه جدول\n");
    printf("7) خروج\n");
    printf("گزینه را وارد کنید: ");
}