#include "../include/compiler.h"

int tosize(const char * src) {
    if(strcmp(src, "byte") == 0) return 1;
    else if(strcmp(src, "word") == 0) return 2;
    else if(strcmp(src, "dword") == 0) return 4;
    else {
        printf("Type %s is not supported\n", src);
        exit(1);
    }
}

long long powx( int val, int exp )
{
    long long actual = val;
    long long prod = 1;
    int i;
    for ( i = 0; i < 32; i++ ) { 
        if ( exp & 0x1 ) {
            prod *= actual;
        }
        exp >>= 1;
        actual *= actual;
    }
    return prod;
}

bytebuffer * compile(tokenlist * list) {
    bytebuffer * out = bytebuffer_create(1);

    for(int i = 0; i < list->ptr; i++) {
        token * tok = list->toks[i];
        if(tok->type == INSTRUCTION) {
            if(strcmp(tok->value, "push") == 0) {
                token * sizetok = list->toks[++i];
                int size = tosize(sizetok->value);
                token * value = list->toks[++i];
                int ivalue = (int)value->value;
                if(size == 1) {
                    bytebuffer_push(out, PUSH8);
                    bytebuffer_push(out, ivalue & 0xff);
                } else if(size == 2) {
                    bytebuffer_push(out, PUSH16);
                    bytebuffer_push(out, (ivalue & 0xff00) >> 8);
                    bytebuffer_push(out, ivalue & 0xff);
                } else if(size == 4) {
                    bytebuffer_push(out, PUSH32);
                    bytebuffer_push(out, (ivalue & 0xff000000) >> 24);
                    bytebuffer_push(out, (ivalue & 0x00ff0000) >> 16);
                    bytebuffer_push(out, (ivalue & 0x0000ff00) >> 8);
                    bytebuffer_push(out, (ivalue & 0x000000ff));
                } else {
                    printf("Type %s is not supported\n", sizetok->value);
                    exit(1);
                }

            } else if(strcmp(tok->value, "add") == 0) {
                token * sizetok = list->toks[++i];
                int size = tosize(sizetok->value);
                switch(size) {
                    case 1: {
                        bytebuffer_push(out, ADD8);
                        break;
                    }
                    case 2: {
                        bytebuffer_push(out, ADD16);
                        break;
                    }
                    case 4: {
                        bytebuffer_push(out, ADD32);
                        break;
                    }
                    default: {
                        printf("Type %s is not supported\n", sizetok->value);
                        exit(1);
                        break;
                    }
                }
            } else if(strcmp(tok->value, "hlt") == 0) {
                bytebuffer_push(out, HLT);
            }
        }
    }
    return out;
}