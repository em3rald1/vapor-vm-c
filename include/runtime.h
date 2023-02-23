#ifndef VAPOR_VM_RUNTIME_H
#define VAPOR_VM_RUNTIME_H

#include "vmstate.h"
#include "bytecode.h"
#include <stdint.h>

void load(vmstate * state, bytebuffer * data, int offset);

uint8_t fetch(vmstate * state);
uint16_t fetch16(vmstate * state);
uint32_t fetch32(vmstate * state);

void push8(vmstate * state, uint8_t val);
void push16(vmstate * state, uint16_t val);
void push32(vmstate * state, uint32_t val);

uint8_t pop8(vmstate * state);
uint16_t pop16(vmstate * state);
uint32_t pop32(vmstate * state);

int step(vmstate * state);
void execute(vmstate * state);


#endif