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

* * 

