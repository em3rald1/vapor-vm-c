#ifndef VAPOR_VM_VMSTATE_H
#define VAPOR_VM_VMSTATE_H

#include "bytebuffer.h"

struct _vmstate {
    bytebuffer * memory;
    uint32_t ip; // instruction pointer
    uint32_t sp; // stack pointer
};

typedef struct _vmstate vmstate;

vmstate * vmstate_create(int memsize);
void vmstate_destroy(vmstate * state);

#endif