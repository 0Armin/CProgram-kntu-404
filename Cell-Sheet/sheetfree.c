void freeSheet(Sheet* sheet) {
    for (int i = 0; i < (*sheet).satr; i++) {
        free((*sheet).cells[i]);
    }
    free((*sheet).cells);
}