# Functions

## x86-64 Stack

* Grows toward lower addresses
* Register %rsp contains lowest stack address (address of top element)
* **pushq Source**
  * Fetch operand at Source
  * Decrement %rsp by 8
  * Write operand at address given by %rsp
* **popq Destination**
  * Read value at address given by %rsp
  * Increment %rsp by 8
  * Store value at Dest (must be register)

## Function Flow

**Control Flow:**

* Procedure call: **callq Function** - calls a function
  * Push return address on stack
  * Jump to label
* Return address
  * Address of the next instruction right after call
* Procedure return: **ret**
  * Pop address from stack
  * Jump to address

**Data Flow:** 

* First 6 arguments to a function will go into:
  * %rdi - 1st argument
  * %rsi - &#8595;
  * %rdx - &#8595;
  * %rcx - &#8595;
  * %r8 - &#8595;
  * %r9 - 6th argument
  * More than 6 arguments: Later arguments will be pushed onto the stack in reverse order (nth argument &#8594; 0th argument)
* **Return value** will always be in **%rax**

## Function Local Data

### Stack Frames

* Contents

  * Return information
  * Local storage (if needed)
  * Temporary space (if needed)

* Management

  * Space allocated when entering a function/procedure
    * Need to set up code by shifting pointers around to correct location (Stack Pointer: %rsp, Frame Pointer: %rbp)
    * Includes push by call instruction
  * Deallocated  when return
    * Clean code by shifting pointers back
    * Includes pop by ret instruction

* Set Up code: subq $N, %rsp = Allocate N bytes of space on the stack

* Clean Up code:  addq $N, %rsp =  Give back N bytes of stack space

* If function f calls function g then f is a caller and g is a callee

  * Caller Saved

    * Caller saves temporary values in its frame before the call

    * | Details                      | Register |
      | ---------------------------- | -------- |
      | **Return value**             | %rax     |
      | **Arguments**                | %rdi     |
      |                              | %rsi     |
      |                              | %rdx     |
      |                              | %rcx     |
      |                              | %r8      |
      |                              | %r9      |
      | **Caller-saved temporaries** | %r10     |
      |                              | %r11     |

      

  * Callee Saved

    * Callee saves temporary values in its frame before using

    * Callee restores them before returning to caller

    * | Details                       | Register |
      | ----------------------------- | -------- |
      | **Callee-saved temporaries**  | %rbx     |
      |                               | %r12     |
      |                               | %r13     |
      |                               | %r14     |
      | **Point to regions of stack** | %rbp     |
      |                               | %rsp     |

## Recursion

* Handled Without Special Consideration
  * Stack frames mean that each function call has private storage
    * Saved registers & local variables
    * Saved return pointer
  * Register saving conventions prevent one function call from corrupting
    another’s data
    * Unless the C code explicitly does so (e.g., buffer overflow in Lecture 9)
  * Stack discipline follows call / return pattern
    * If P calls Q, then Q returns before P
    * Last-In, First-Out