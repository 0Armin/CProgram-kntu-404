#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "split_input.h"
#include "calculate.h"

void free_list(part_list list);

double formula(char *input){

    part_list list = split(input);

    double result = calculate(&list);

    free_list(list);

    return result;
}