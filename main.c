#include "Cell-Sheet/sheet.h"
#include "formula.h"
#include "split_input.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void menu();

int main() {

    Sheet sheet;
    int init = 0;

    while (1) {

        menu();
        int choice;
        scanf("%d", &choice);

        if (choice == 1){
            int satr, soton;
            printf("Satr: ");
            scanf("%d", &satr);
            printf("Soton: ");
            scanf("%d", &soton);

            initSheet(&sheet, satr, soton);
            init = 1;

            printf("Jadval meghdardehi shod\n");
        }

        else if (choice == 2) {

            if (!init) {
                printf("Meghdar dehi avaliye anjam shavad\n");
                continue;
            }

            char address[10];
            char input[256];
            int ch;
            double value;

            printf("Address: ");
            scanf("%s", address);

            printf("Vorodi: ");

            while ((ch = getchar()) != '\n' && ch != EOF);

            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("Khataei dar vorodi\n");
                continue;
            }

            input[strcspn(input, "\n")] = '\0';

            value = formula(input, &sheet);

            if (setCellValue(&sheet, address, value))
                printf("Meghdar tanzim shod\n");
            else
                printf("Khataei: address namotabar\n");
        }

        else if (choice == 3) {

            if (!init) {
                printf("Meghdar dehi avaliye anjam shavad\n");
                continue;
            }

            char address[10];
            char formula[Max_formula_tol];
            int ch;

            printf("Address: ");
            scanf("%s", address);

            printf("Formula: ");

            while ((ch = getchar()) != '\n' && ch != EOF);

            if (fgets(formula, sizeof(formula), stdin) == NULL) {
                printf("Khataei dar vorodi\n");
                continue;
            }

            formula[strcspn(formula, "\n")] = '\0';

            if (!sanitize_Formula(formula)) {
                printf("Formula namotabr\n");
                continue;
            }

            if (setCellFormula(&sheet, address, formula))
                printf("Formula tanzim shod\n");
            else
                printf("Khataei: address namotabar\n");
        }

        else if (choice == 4) {

            if (!init) {
                printf("Meghdar dehi avaliye anjam shavad\n");
                continue;
            }

            printSheet(&sheet);
        }

        else if (choice == 5) {

            if (!init) {
                printf("Meghdar dehi avaliye anjam shavad\n");
                continue;
            }

            int maxsatr, maxsoton;
            printf("Bishtarin satr: ");
            scanf("%d", &maxsatr);
            printf("Bishtarin soton: ");
            scanf("%d", &maxsoton);

            printSheet_mahdod(&sheet, maxsatr, maxsoton);
        }

        else if (choice == 6) {

            if (!init) {
                printf("Meghdar dehi avaliye anjam shavad\n");
                continue;
            }

            int satr_jadid, soton_jadid;
            printf("Satr jadid: ");
            scanf("%d", &satr_jadid);
            printf("Soton jadid: ");
            scanf("%d", &soton_jadid);

            taghir_size_Sheet(&sheet, satr_jadid, soton_jadid);

            printf("Andaze jadval taghir kard\n");
        }

        else if (choice == 7) {
            printf("Khoroj az barname\n");
            break;
        }
        else {
            printf("Gozine namotabar\n");
        }
    }
    if (init)
        freeSheet(&sheet);

    return 0;
}
void menu() {
    printf("\n===== main menu =====\n");
    printf("1) Meghdardehi avaliye jadval\n");
    printf("2) Tanzim meghdar yek selol\n");
    printf("3) Tanzim formula yek selol\n");
    printf("4) Print kamel jadval \n");
    printf("5) Print mahdod jadval\n");
    printf("6) Taghir andaze jadval\n");
    printf("7) Khoroj\n");
    printf("Gozine vared konid: ");
}