#include "../include/lexer.h"

lexer * lexer_create(const char * src) {
    lexer * lex = (lexer*)malloc(sizeof(lexer));
    lex->toklist = tokenlist_create(1);
    lex->ptr = 0;
    lex->size = strlen(src);
    lex->src = (char*)src;
    return lex;
}
void lexer_destroy(lexer * lex) {
    tokenlist_destroy(lex->toklist);
    free(lex);
}

void lexer_tokenize(lexer * lex) {
    int cindex = 1;
    int lindex = 1;
    while(lex->ptr != lex->size) {
        char c = lex->src[lex->ptr];

        if(c == ' ') {
            cindex++;
            lex->ptr++;
        } else if(c == '\n') {
            lindex++;
            cindex = 1;
            lex->ptr++;
        } else if(c == '\t') {
            cindex++;
            lex->ptr++;  
        } else if(isdigit(c)) {
            int x = c - '0';
            int cstart = cindex;
            lex->ptr++;
            while(isdigit(lex->src[lex->ptr]) && lex->src[lex->ptr] != 0) {
                x *= 10;
                x += (lex->src[lex->ptr++] - '0');
                cindex++;
            }
            token * tok = (token*)malloc(sizeof(token));
            tok->type = NUMBER;
            tok->start = cstart;
            tok->value = (void*)x;
            tok->line = lindex;
            tokenlist_push(lex->toklist, tok);
        } else if(c == '.') {
            char * x  = (char*)malloc(sizeof(char)*10);
            int xptr = 0;
            int xsize = 10;
            lex->ptr++;
            int cstart = cindex;
            while(lex->src[lex->ptr] != 0 && strchr(" \n\t.", lex->src[lex->ptr]) == NULL) {
                if(xptr >= xsize) {
                    xsize *= 2;
                    x = (char*)realloc(x, sizeof(char)*xsize);
                    
                }
                x[xptr++] = lex->src[lex->ptr++];
                cindex++;
            }
            token * tok = (token*)malloc(sizeof(token));
            tok->type = LABEL;
            tok->start = cstart;
            tok->line = lindex;
            tok->value = x;
            tokenlist_push(lex->toklist, tok);
        } else {
            char * x = (char*)malloc(sizeof(char)*10);
            int xptr = 0;
            int xsize = 10;
            int cstart = cindex;
            while(lex->src[lex->ptr] != 0 && strchr(" \n\t.", lex->src[lex->ptr]) == NULL) {
                if(xptr >= xsize) {
                    xsize *= 2;
                    x = (char*)realloc(x, sizeof(char)*xsize);
                    
                }
                x[xptr++] = lex->src[lex->ptr++];
                cindex++;
            }
            token * tok = (token*)malloc(sizeof(token));
            tok->type = INSTRUCTION;
            tok->start = cstart;
            tok->line = lindex;
            tok->value = x;
            tokenlist_push(lex->toklist, tok);
        }
    }
    token * tok = (token*)malloc(sizeof(token));
    tok->type = EOF;
    tok->start = cindex;
    tok->line = lindex;
    tok->value = (void*)NULL;
    tokenlist_push(lex->toklist, tok);
}