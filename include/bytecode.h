#ifndef VAPOR_VM_BYTECODE_H
#define VAPOR_VM_BYTECODE_H

enum _bytecode {
    PUSH8, // PUSH 8 bit value onto the stack
    PUSH16, // PUSH 16 bit value onto the stack
    PUSH32, // PUSH 32 bit value onto the stack
    POP8, // POP 8 bit value off the stack, effectively deleting the value
    POP16, // POP 16 bit value off the stack
    POP32, // POP 32 bit value off the stack
    DUP8, // DUPlicate 8 bit value on the stack
    DUP16, // DUPlicate 16 bit value on the stack
    DUP32, // DUPlicate 32 bit value on the stack

    ADD8, // pop 2 8 bit values off the stack, ADD them, push the result
    ADD16, // pop 2 16 bit values off the stack, ADD them, push the result
    ADD32, // pop 2 32 bit values off the stack, ADD them, push the result

    SUB8, // pop 2 8 bit values off the stack, SUBtract one from another, push the result
    SUB16, // pop 2 16 bit values off the stack, SUBtract one from another, push the result
    SUB32, // pop 2 32 bit values off the stack, SUBtract one from another, push the result

    MUL8,
    MUL16,
    MUL32,

    DIV8,
    DIV16,
    DIV32,

    MOD8,
    MOD16,
    MOD32,

    PRT, // (PRint Text) Equivalent to OUT %text VAL in URCL
    INT, // (INput Text) Equivalent to IN Rx %text in URCL
    PRN, // (PRint Number) Equivalent to OUT %numb VAL in URCL
    INN, // (INput Number) Equivalent to IN Rx %numb

    BRA, // unconditional BRAnch

    CMP8, // CoMPare 2 8 bit values on the stack, if less, (byte)-1 will be on the stack, if greater, (byte)1 will be on the stack, if equals, (byte)0 will be on the stack
    CMP16, // CoMPare 2 16 bit values on the stack, if less (word)-1 will be on the stack, if greater, (word)1 will be on the stack, if equals, (word)0 will be on the stack
    CMP32, // CoMPare 2 32 bit values on the stack, if less (dword)-1 will be on the stack, if greater, (dword)1 will be on the stack, if equals, (dword)0 will be on the stack
    

    STR8, // Gets 32 bit address from the stack, 8 bit value and SToRes value at address
    STR16, // Gets 32 bit address from the stack, 16 bit value and SToRes value at address
    STR32, // Gets 32 bit address and value from the stack, and SToRes value at address

    LOD8, // Gets 32 bit address from the stack and LOaDs 8 bit value on the stack
    LOD16, // Gets 32 bit address from the stack and LOaDs 16 bit value on the stack
    LOD32, // Gets 32 bit address from the stack and LOaDs 32 bit value on the stack

    HLT,
};

#endif // VAPOR_VM_BYTECODE_H