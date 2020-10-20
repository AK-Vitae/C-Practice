# Data Structures Implementations in C



## Array Sorting

**Input:**  A command-line input. The first line in the file provides the total number of values in the array. The second line will contain a list of numbers separated by tabs.

**Output:** The output will be the sorted list of numbers, even numbers (ascending) and then odd numbers (descending), each separated by tabs.



## Linked List

**Input:** This program takes a file name as a command-line argument. The file contains a number of lines of input (possibly 0). Each line contains a character, either **i** or d, followed by a tab character, and then an integer.

* If the line starts with **i**, your program should insert that number in the linked list in sorted order. If it is already present, your program can insert it before or after the existing entry.
* If the line starts with a **d**, your program should delete the value from the linked list. If there are duplicates, your program should delete only the first occurrence of the value. If the requested value is not present in the linked list, your program should ignore this line of the input.

**Output:** If the input file doesn’t exist, your program should print error. Otherwise, your program should print two lines of output: 

* The number of nodes in the list (including duplicates) 
* A tab-separated list of the values of the linked list in order, with duplicate values only printed once



## Hash Table

A Hash Table containing 10000 buckets, with collision resolution resolved using chaining via a linked list.

**Input:** This program takes a file name as a command-line argument. Each line of the file contains a character, either i or s, followed by a tab and then an integer. 

* For each line that starts with i, your program should insert that number in the hash table if it is not present. 
* If the line starts with a s, your program should search the hash table for that value.

**Output:** The program should print two counts: 

* The number of insertions where a collision occurred (including due to duplicate values) 
* The number of successful searches (where the value was present).



## String Operations

**Input:** This program takes a string of space-separated words

**Output:** A single word containing only the vowels of the inputted string



## Binary Search Tree

**Input:** This program takes a file name as a command-line argument. The file is either blank or contains successive lines of input. 

* Each line starts with i followed by a tab and then an integer. 
* The program should insert that number in the binary search tree if it is not already there. 
* If it is already present, you should ignore that line of input.

**Output:** If the input file does not exist, your program should print error. Otherwise, your program should print a single tab-separated line containing all the elements in the tree in ascending order.