#include "../include/bytebuffer.h"

bytebuffer * bytebuffer_create(int size) {
    bytebuffer * buf = (bytebuffer*)malloc(sizeof(bytebuffer));
    buf->size = size;
    buf->ptr = 0;
    buf->data = (uint8_t*)malloc(size*sizeof(uint8_t));
    return buf;
}
void bytebuffer_destroy(bytebuffer * buf) {
    free(buf->data);
    free(buf);
}
void bytebuffer_clean(bytebuffer * buf) {
    free(buf->data);
    buf->data = (uint8_t*)malloc(buf->size * sizeof(uint8_t));
}

void bytebuffer_push(bytebuffer * buf, uint8_t data) {
    if(buf->ptr >= buf->size) {
        buf->size *= 2;
        buf->data = (uint8_t*)realloc(buf->data, buf->size);
    }
    buf->data[buf->ptr++] = data;
}
uint8_t bytebuffer_pop(bytebuffer * buf) {
    if(buf->ptr != 0) {
        return buf->data[--buf->ptr];
    }
}

void bytebuffer_write8(bytebuffer * buf, int addr, uint8_t data) {
    buf->data[addr] = data;
}
void bytebuffer_write16(bytebuffer * buf, int addr, uint16_t data) {
    bytebuffer_write8(buf, addr, (data & 0xff00) >> 8);
    bytebuffer_write8(buf, addr+1, data & 0xff);
}
void bytebuffer_write32(bytebuffer * buf, int addr, uint32_t data) {
    bytebuffer_write16(buf, addr, (data & 0xffff0000) >> 16);
    bytebuffer_write16(buf, addr+2, data & 0xffff);
}
uint8_t bytebuffer_read8(bytebuffer * buf, int addr) {
    return buf->data[addr];
}
uint16_t bytebuffer_read16(bytebuffer * buf, int addr) {
    uint8_t upper = bytebuffer_read8(buf, addr);
    uint8_t lower = bytebuffer_read8(buf, addr+1);
    return (upper << 8) | lower;
}
uint32_t bytebuffer_read32(bytebuffer * buf, int addr) {
    uint16_t upper = bytebuffer_read16(buf, addr);
    uint16_t lower = bytebuffer_read16(buf, addr+2);
    return (upper << 16) | lower;
}
void bytebuffer_print(bytebuffer * buf) {
    for(int i = 0; i < buf->size; i++) {
        printf("%02x ", buf->data[i]);
    }
}