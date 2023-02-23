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