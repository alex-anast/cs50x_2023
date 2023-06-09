#Problem 1.1 - debug

This project involves debugging a C program with syntactical errors. The objective is to try and compile the program, understand and interpret the error messages generated by the compiler, and then debug the program.

## Learning Goals

- Familiarity with C syntax
- Understanding C compiler error messages
- Practice debugging programs
- The Problem

The code provided has several syntactical errors, which are preventing the program from compiling properly. The program should prompt the user for their name and location and then greet them. Your job is to identify and fix these errors.

The following are some of the errors that could occur in the program:

- undefined reference to 'get_string' error occurs because the cs50 library is not linked properly. We can fix this by adding -lcs50 in the makefile and linking it correctly.
- undeclared identifier: string error occurs because the string data type is not declared in the program. We can fix this by including the string.h header file.
- expected ';' at end of declaration error occurs because there is a missing semicolon in the code. We can fix this by adding a semicolon at the end of the line.
- format specifies type 'char *' but the argument has type 'string' error occurs because printf expects a char * as input, but we are passing a string data type. We can fix this by using %s instead of %c.

After correcting these errors, the final code will compile and run without any issues.
