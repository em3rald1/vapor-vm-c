#ifndef VAPOR_VM_BYTEBUFFER_H
#define VAPOR_VM_BYTEBUFFER_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

struct _bytebuffer {
    uint8_t * data;
    int ptr;
    int size;
};

typedef struct _bytebuffer bytebuffer;

bytebuffer * bytebuffer_create(int size);
void bytebuffer_destroy(bytebuffer * buf);
void bytebuffer_clean(bytebuffer * buf);

void bytebuffer_push(bytebuffer * buf, uint8_t data);
uint8_t bytebuffer_pop(bytebuffer * buf);

void bytebuffer_write8(bytebuffer * buf, int addr, uint8_t data);
void bytebuffer_write16(bytebuffer * buf, int addr, uint16_t data);
void bytebuffer_write32(bytebuffer * buf, int addr, uint32_t data);
uint8_t bytebuffer_read8(bytebuffer * buf, int addr);
uint16_t bytebuffer_read16(bytebuffer * buf, int addr);
uint32_t bytebuffer_read32(bytebuffer * buf, int addr);

void bytebuffer_print(bytebuffer * buf);

#endif // VAPOR_VM_BYTEBUFFER_H