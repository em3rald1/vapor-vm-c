#ifndef VAPOR_VM_COMPILER_H
#define VAPOR_VM_COMPILER_H

#include "bytebuffer.h"
#include "bytecode.h"
#include "token.h"

bytebuffer * compile(tokenlist * list);

#endif