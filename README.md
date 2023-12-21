# Holberton School Simple Shell Project

## Description

This is a custom implementation of a "simple shell" in C, created as part of the Holberton School curriculum. 
The project includes a set of functions to handle different format specifiers, such as `%c` for characters, `%s` for strings, `%d` and `%i` for integers, and `%` for percent signs.

## Files

- `main.h`: Header file containing function prototypes and necessary includes.
- `simple_shell_main.c`: The main function of the shell.
- `print_character`: Implementation of the function to print characters.
- `print_percent`: Implementation of the function to print percent signs.
- `print_digit`: Implementation of the function to print integers.
- `_printf`: Implementation of the main `_printf` function.
- `sp_functions`: Implementation of supporting functions for various specifiers.
- `man_3_printf`: Manual page for the custom `printf` function.

## Usage

To use the custom `printf` function, include the `main.h` header file in your program and call `_printf` with the desired format string and arguments.

```c
#include "main.h"

int main(void)
{
    _printf("Hello, %s!\n", "world");
    _printf("The answer is %d.\n", 42);

    return 0;
}
```
### Compilation
``` bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c
```

### Man page
``` bash
man ./man_3_printf
```
### Examples

Printing a character:
```
_printf("The first letter of the alphabet is %c.\n", 'A');
```
----------
Printing a string:
```
_printf("Welcome to %s!\n", "Holberton School");
```
----------
Printing an integer:
```
_printf("The result of 5 x 5 = %d.\n", 25);
```
----------
Printing a percent sign:
```
_printf("This is a 100%% accurate statement.\n");
```
----------

## Flowchart

![Image](https://github.com/Yasine31130/holbertonschool-printf/blob/main/Flowchart.png)

## Authors

- Nathan Raynal
