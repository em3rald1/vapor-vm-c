#include "../include/token.h"

tokenlist * tokenlist_create(int size) {
    tokenlist * list = (tokenlist*)malloc(sizeof(tokenlist));
    list->size = size;
    list->ptr = 0;
    list->toks = (token**)malloc(size*sizeof(token*));
}
void tokenlist_destroy(tokenlist * list) {
    free(list->toks);
    free(list);
}
void tokenlist_push(tokenlist * list, token * tok) {
    if(list->ptr >= list->size) {
        list->size *= 2;
        list->toks = (token**)realloc(list->toks, list->size * sizeof(token*));
    }
    list->toks[list->ptr++] = tok;
}

void token_print(token* tok) {
    printf("<Token type=%d value=%p line=%d start=%d>\n", tok->type, tok->value, tok->line, tok->start);
}

void tokenlist_print(tokenlist * list) {
    printf("<Tokenlist toks=[\n");
    for(int i = 0; i < list->ptr; i++) {
        printf("\t");
        token_print(list->toks[i]);
    }
    printf("] ptr=%d size=%d>\n", list->ptr, list->size);
}