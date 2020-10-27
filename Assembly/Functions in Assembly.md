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

