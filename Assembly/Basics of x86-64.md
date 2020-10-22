# Basics

## x86-64 Integer Registers

| Register                                                     | Low-Order 4 Bytes |
| ------------------------------------------------------------ | ----------------- |
| %rax - register a extended                                   | %eax              |
| %rbx - register b extended                                   | %ebx              |
| %rcx - register c extended                                   | %ecx              |
| %rdx - register d extended                                   | %edx              |
| %rbp - register base pointer (start of stack)                | %esi              |
| %rsp - register stack pointer (current location in stack, growing downwards) | %edi              |
| %rsi - register source index (source for data copies)        | %esp              |
| %rdi - register destination index (destination for data copies) | %ebp              |

The registers added for 64-bit mode are named:

- %r8 - register 8
- %r9 - register 9
- %r10 - register 10
- %r11 - register 11
- %r12 - register 12
- %r13 - register 13
- %r14 - register 14
- %r15 - register 15

## movq Source, Destination

| Source                           | Destination | Source, Destination | C Analog       |
| -------------------------------- | ----------- | ------------------- | -------------- |
| Immediate(Constant Integer data) | Register    | movq $123, %rax     | temp = 0x4;    |
| Immediate(Constant Integer data) | Memory      | movq $-147,(%rax)   | *p = -147;     |
| Register                         | Register    | movq %rax,%rdx      | temp2 = temp1; |
| Register                         | Memory      | movq %rax,(%rdx)    | *p = temp;     |
| Memory (Dereferencing)           | Register    | movq (%rax),%rdx    | temp = *p;     |

Cannot do memory-memory transfer with a single instruction

### Complete Memory Addressing Modes

* **movq (%rcx),%rax** = copying **Memory[Reg[R]]** into rax = copying Memory[rcx] into rax
* **movq 8(%rbp),%rdx** = copying **Memory[Reg[R]+D]** into rdx = copying Memory[rbp+8] into rdx
* **movq 8(%rbp,%rax,4),%rdx** = copying **Memory[Reg[Rb]+S*Reg[Ri]+D]** into rdx = copying Memory[rbp+4 *rax+8] into rdx
* **D:** Constant “displacement” 1, 2, or 4 bytes
* **Rb:** Base register: Any of 16 integer registers
* **Ri:** Index register: Any, except for %rsp
* **S:** Scale: 1, 2, 4, or 8

## leaq Source, Destination

* Computing addresses without a memory reference
* **leaq (%rdi,%rdi,2), %rax**

## Arithmetic Operations (Format: Source,Destination )

| Operation | Computation                          |
| --------- | ------------------------------------ |
| addq      | Destination = Destination + Source   |
| subq      | Destination = Destination - Source   |
| imulq     | Destination = Destination * Source   |
| salq      | Destination = Destination << Source  |
| sarq      | Destination = Destination >> Source  |
| shrq      | Destination = Destination >> Source  |
| xorq      | Destination = Destination ^ Source   |
| andq      | Destination = Destination & SSourcec |
| orq       | Destination = Destination \| Source  |
| incq      | Destination = Destination + 1        |
| decq      | Destination = Dest - 1               |
| negq      | Destination = -Destination           |
| notq      | Destination = ~Destination           |

