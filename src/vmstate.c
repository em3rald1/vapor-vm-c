#include "../include/vmstate.h"

vmstate * vmstate_create(int memsize) {
    vmstate * state = (vmstate*)malloc(sizeof(vmstate));
    state->memory = bytebuffer_create(memsize);
    for(int i = 0; i < state->memory->size; i++) {
        state->memory->data[i] = 0;
    }
    state->ip = 0;
    state->sp = memsize;
}
void vmstate_destroy(vmstate * state) {
    bytebuffer_destroy(state->memory);
    free(state);
}