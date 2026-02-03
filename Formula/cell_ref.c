#include "formula.h"

double cell_refrence(Sheet *sheet, char input[], int *err){
    if (!sheet || !input)
    {
        *err = ERR_EMPTY_INPUT;
        return 0;
    }

    Cell *cell = getCell(sheet, input);
    if (!cell)
    {
        *err = ERR_INVALID_CELL;
        return 0;
    }

    return cell->value;
}