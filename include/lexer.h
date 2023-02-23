#ifndef VAPOR_VM_LEXER_H
#define VAPOR_VM_LEXER_H

#include "token.h"
#include <string.h>
#include <ctype.h>

struct _lexer {
    tokenlist * toklist;
    char * src;
    int ptr;
    int size;
};

typedef struct _lexer lexer;

lexer * lexer_create(const char * src);
void lexer_destroy(lexer * lex);

void lexer_tokenize(lexer * lex);

#endif