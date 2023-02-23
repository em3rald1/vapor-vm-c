#include "../include/lexer.h"
#include <stdio.h>

int main() {
    const char * src = "MOV R1 54\n.label1\nX 514 132\nJMP .label1";
    printf("SOURCE:\n%s\n", src);
    lexer * lex = lexer_create(src);
    lexer_tokenize(lex);
    printf("Tokenizing finished\n");
    printf("TOKENS:\n");
    for(int i = 0; i < lex->toklist->ptr; i++) {
        printf("<Token type=%d, value=%p, char=%d, line=%d>\n", lex->toklist->toks[i]->type, lex->toklist->toks[i]->value, lex->toklist->toks[i]->start, lex->toklist->toks[i]->line);
    }
    lexer_destroy(lex);
}