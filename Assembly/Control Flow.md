## Condition Codes

**Single Bit Registers**

* CF = Carry Flag (for unsigned) 
* SF = Sign Flag (for signed)
* ZF = Zero Flag 
* OF = Overflow Flag (for signed)

**Implicitly set (think of it as side effect) by arithmetic operations**

* Example 1: addq Source,Destination ↔ t = a+b
  * CF set if carry out from most significant bit (unsigned overflow)
  * ZF set if t == 0
  * SF set if t < 0 (as signed)
  * OF set if two’s-complement (signed) overflow
    * (a>0 && b>0 && t<0) || (a<0 && b<0 && t>=0)

*  Example 2: **cmpq Source2, Source1 = Source1 - Source2**
  *  CF set if carry out from most significant bit (used for unsigned comparisons)
  *  ZF set if a == b
  * SF set if (a-b) < 0 (as signed)
  * OF set if two’s-complement (signed) overflow
    * (a>0 && b<0 && (a-b)<0) || (a<0 && b>0 && (a-b)>0)

* Example 2: **testq Source2, Source1 = Source1&Source2**
  *  ZF set when a&b == 0
  * SF set when a&b < 0

**NOT set by leaq instruction**

### SetX Instructions

| SetX | Condition     | Description               |
| ---- | ------------- | ------------------------- |
| sete | ZF            | Equal / Zero              |
| sete | ~ZF           | Not Equal / Not Zero      |
| sete | SF            | Negative                  |
| sete | ~SF           | Nonnegative               |
| sete | ~(SF^OF)&~Z   | Greater (Signed)          |
| sete | ~(SF^OF)      | Greater or Equal (Signed) |
| sete | (SF^OF)       | Less (Signed)             |
| sete | (SF^OF) \| ZF | Less or Equal (Signed)    |
| sete | ~CF&~ZF       | Above (unsigned)          |
| sete | CF            | Below (unsigned)          |

**movzbl Source, Destination** = moves source byte to destination and then zeros out everything higher than byte

## Jumping

Jump to different part of code depending on condition codes

### jX Instructions

| jX   | Condition     | Description               |
| ---- | ------------- | ------------------------- |
| jmp  | 1             | unconditional             |
| je   | ZF            | Equal / Zero              |
| jne  | ~ZF           | Not Equal / Not Zero      |
| js   | SF            | Negative                  |
| jns  | ~SF           | Nonnegative               |
| jg   | ~(SF^OF)&~Z   | Greater (Signed)          |
| jge  | ~(SF^OF)      | Greater or Equal (Signed) |
| jl   | (SF^OF)       | Less (Signed)             |
| jle  | (SF^OF) \| ZF | Less or Equal (Signed)    |
| ja   | ~CF&~ZF       | Above (unsigned)          |
| jb   | CF            | Below (unsigned)          |

**Direct Jump**: jmp .L8

**Indirect Jump**: jmp *.L4(,%rdi,8) = jmp .L4 + x *8