#include "sheet.h"
#include "formula.h"
#include "split_input.h"
#include <stdio.h>
#include <string.h>

void menu();

int main() {
    printf("Program started!\n");
    
    Sheet sheet;
    int init = 0;
    menu();

    while (1) {
        menu();
        int choice;
        scanf("%d", &choice);
        if (choice == 1){
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
            char input[256];
            int ch;
            double value;

            printf("cell address like A1");
            scanf("%s", address);

            printf("input: ");
            while ((ch = getchar()) != '\n' && ch != EOF);
            if (fgets(input, sizeof(input), stdin) == NULL)
            {
            printf("Input error\n");
            break;
            }
            input[strcspn(input, "\n")] = '\0';
            value = formula(input, &sheet);

            if (setCellValue(&sheet, address, value))
                printf("done\n");
            else
                printf("error address wrong\n");
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
    printf("\n===== main menu =====\n");
    printf("1) initilize\n");
    printf("2) set cell\n");
    printf("3) set formula for cell\n");
    printf("4) print full cell\n");
    printf("5) print specific\n");
    printf("6) change size of table\n");
    printf("7) exit\n");
    printf("enter your choice: ");
}