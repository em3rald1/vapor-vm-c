#ifndef VAPOR_VM_TOKEN_H
#define VAPOR_VM_TOKEN_H

#include <stdlib.h>
#include <stdio.h>

enum _tokentype {
    INSTRUCTION,
    NUMBER,
    LABEL,
    _EOF
};

typedef enum _tokentype tokentype;

struct _token {
    tokentype type;
    void * value;
    int line;
    int start;
};

typedef struct _token token;

struct _tokenlist {
    token ** toks;
    int size;
    int ptr;
};

typedef struct _tokenlist tokenlist;

tokenlist * tokenlist_create(int size);
void tokenlist_destroy(tokenlist * list);
void tokenlist_push(tokenlist * list, token * tok);

void token_print(token* tok);

void tokenlist_print(tokenlist * list);

#endif // VAPOR_VM_TOKEN_H