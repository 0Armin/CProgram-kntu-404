#include <stdio.h>
#include "split_input.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void meghdardehi(part_list *list){
    list->items = NULL;
    list->current = 0;
    list->maximum = 0;
}

static void add_part(part_list *list, part p){
    if (list->current == list->maximum)
    {
        int new_max;
        if (list->maximum == 0)
        {
            new_max = 8;
        } else {
            new_max = (list->maximum)*2;
        }
        
        list->items = realloc(list->items, new_max*sizeof(part));
        list->maximum = new_max;
    }
    list->items[list->current] = p;
    list->current++;
}

part_list split(char *text){
    part_list list;
    meghdardehi(&list);

    int i=0;

    while (text[i] != '\0')
    {
        if (isspace(text[i]))
        {
            i++;
            continue;
        }

        if (isdigit(text[i]) || text[i] == '.')
        {
            char *end;
            double value = strtod(&text[i],&end);

            part p;
            p.noe = number;
            p.number = value;
            p.text_name = NULL;

            add_part(&list, p);
            i = end - text;
            continue;
        }
        
        if (isalpha(text[i]))
        {
            int start = i;
            int length;
            while (isalpha(text[i]))
            {
                i++;
            }
            length = i-start;
            char *name = malloc(length + 1);
            strncpy(name, &text[start], length);
            name[length]= '\0';

            part p;
            p.noe = function;
            p.number = 0;
            p.text_name = name;

            add_part(&list, p);
            continue;

        }
        
        if (strchr("+-*/^", text[i]))
        {
            part p;
            p.noe = operator;
            p.number = 0;
            p.text_name = malloc(2);
            p.text_name[0] = text[i];
            p.text_name[1] = '\0';

            add_part(&list, p);
            i++;
            continue;
        }

        if (text[i] == '(')
        {
            part p;
            p.noe = s_parantes;
            p.number = 0;
            p.text_name = NULL;
            add_part(&list, p);
            i++;
            continue;
        }
        
        if (text[i] == ')')
        {
            part p;
            p.noe = s_parantes;
            p.number = 0;
            p.text_name = NULL;
            add_part(&list, p);
            i++;
            continue;
        }
    }

    return list;
}
