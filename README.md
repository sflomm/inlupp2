# Inlupp 2
***
This is a README file for assignment 2 of the IOOPM-course.
The assignment is based on the previous task assignment.\
This program was created by Ella Odlander and Simon Funke in the autumn 2026.
## How to use the program
*** 
The program is a basic protype of a backend webstore. It has a text based menu which requires user input. Some of the actions possible in the program are add/remove/edit merchandise and shopping carts. The actions made are not saved, it only exists while the program runs. 
### How to run the program
*** 
1. Download the repository. 
2. Use the following terminal command to run the program:
```bash
make run
```

## Running tests
***
Use the following terminal commands to run different tests:
1.  To run test
```bash
make test
```
2. To run the test through valgrind
```bash
make valgrind
```
3. To remove compiled files
```bash
make clean
```
## Coverage
***
We used gcov to collect coverage data for branch and code line coverage.\
Use this make command:
```bash
make coverage
```
Should get the following data:
| FILE          | Lines         |  Exec   | Cover   | Branches| Taken | Cover |
| ------------- | ------------- | ------- | ------- | ------- | ----- |------ |
| cart_calc.c   | 122           | 105     | 86%     |    48   |  32   |  66%  |
| merch_stock.c | 129           | 121     | 93%     |    34   |  26   |  76%  |

## Pointers as keys or values
***
The hashtable implementation does not take ownership of keys and values that are some sort of pointer. Other fields of elem_t are owned by the hashtable.
