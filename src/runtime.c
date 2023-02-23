#include "../include/runtime.h"
#include <stdio.h>
void load(vmstate * state, bytebuffer * data, int offset) {
    for(int i = 0; i < data->ptr; i++) {
        if(state->memory->size > offset+i) {
            state->memory->data[offset+i] = data->data[i];
        }
    }
}

uint8_t fetch(vmstate * state) {
    return state->memory->data[state->ip++];
}

uint16_t fetch16(vmstate * state) {
    uint8_t upper = fetch(state);
    uint8_t lower = fetch(state);
    return (upper << 8) | lower;
}

uint32_t fetch32(vmstate * state) {
    uint16_t upper = fetch16(state);
    uint16_t lower = fetch16(state);
    return (upper << 16) | lower;
}


void push8(vmstate * state, uint8_t val) {
    state->memory->data[--state->sp] = val;
}
void push16(vmstate * state, uint16_t val) {
    uint8_t upper = (val & 0xff00) >> 8;
    uint8_t lower = val & 0xff;
    push8(state, lower);
    push8(state, upper);
}
void push32(vmstate * state, uint32_t val) {
    uint8_t upper = (val & 0xffff0000) >> 16;
    uint8_t lower = val & 0xffff;
    push16(state, lower);
    push16(state, upper);
}

uint8_t pop8(vmstate * state) {
    return state->memory->data[state->sp++];
}
uint16_t pop16(vmstate * state) {
    uint8_t upper = pop8(state);
    uint8_t lower = pop8(state);
    return (upper << 8) | lower;
}
uint32_t pop32(vmstate * state) {
    uint16_t upper = pop16(state);
    uint16_t lower = pop16(state);
    return (upper << 16) | lower;
}

int step(vmstate * state) {
    uint8_t inst = fetch(state);
    switch(inst) {
        case PUSH8: {
            uint8_t data = fetch(state);
            push8(state, data);
            break;
        }
        case PUSH16: {
            uint16_t data = fetch16(state);
            push16(state, data);
            break;
        }
        case PUSH32: {
            uint32_t data = fetch32(state);
            push32(state, data);
            break;
        }
        case ADD8: {
            uint8_t lhs = pop8(state);
            uint8_t rhs = pop8(state);
            push8(state, lhs + rhs);
            break;
        }
        case ADD16: {
            uint16_t lhs = pop16(state);
            uint16_t rhs = pop16(state);
            push16(state, lhs + rhs);
            break;
        }
        case ADD32: {
            uint32_t lhs = pop32(state);
            uint32_t rhs = pop32(state);
            push32(state, lhs + rhs);
            break;
        }

        case SUB8: {
            uint8_t rhs = pop8(state);
            uint8_t lhs = pop8(state);
            push8(state, lhs - rhs);
            break;
        }
        case SUB16: {
            uint16_t rhs = pop16(state);
            uint16_t lhs = pop16(state);
            push16(state, lhs - rhs);
            break;
        }
        case SUB32: {
            uint32_t rhs = pop32(state);
            uint32_t lhs = pop32(state);
            push32(state, lhs - rhs);
            break;
        }

        case STR8: {
            uint8_t value = pop8(state);
            uint32_t addr = pop32(state);
            bytebuffer_write8(state->memory, addr, value);
            break;
        }
        case STR16: {
            uint16_t value = pop16(state);
            uint32_t addr = pop32(state);
            bytebuffer_write16(state->memory, addr, value);
            break;
        }
        case STR32: {
            uint32_t value = pop32(state);
            uint32_t addr = pop32(state);
            bytebuffer_write32(state->memory, addr, value);
            break;
        }
        case LOD8: {
            uint32_t addr = pop32(state);
            push8(state, bytebuffer_read8(state->memory, addr));
            break;
        }
        case LOD16: {
            uint32_t addr = pop32(state);
            uint16_t val = bytebuffer_read16(state->memory, addr);
            push16(state, val);
            break;
        }
        case LOD32: {
            uint32_t addr = pop32(state);
            push32(state, bytebuffer_read32(state->memory, addr));
            break;
        }
        case POP8: {
            uint32_t addr = pop32(state);
            push8(state, state->memory->data[addr]);
            break;
        }
        case HLT: {
            return 1;
        }
    }
    return 0;
}
void execute(vmstate * state) {
    int res = 0;
    while(res == 0) {
        res = step(state);
    }
}