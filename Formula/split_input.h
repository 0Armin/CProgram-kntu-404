#ifndef SPLIT_INPUT_H
#define SPLIT_INPUT_H

typedef enum{
    number,
    operator,
    function,
    s_parantes,
    e_parantes
} type;

typedef struct
{
    part *items;
    int current;
    int maximum;
} part_list;

typedef struct
{
    type noe;
    double number;
    char *text_name;
} part;

part_list split(char *text);

#endif