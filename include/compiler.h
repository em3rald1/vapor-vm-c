#ifndef VAPOR_VM_COMPILER_H
#define VAPOR_VM_COMPILER_H

#include "bytebuffer.h"
#include "bytecode.h"
#include "token.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

bytebuffer * compile(tokenlist * list);

#endif