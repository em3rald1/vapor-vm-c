#include "../include/vmstate.h"

vmstate * vmstate_create(int memsize) {
    vmstate * state = (vmstate*)malloc(sizeof(vmstate));
    state->memory = bytebuffer_create(memsize);
    state->ip = 0;
    state->sp = memsize;
}
void vmstate_destroy(vmstate * state) {
    bytebuffer_destroy(state->memory);
    free(state);
}