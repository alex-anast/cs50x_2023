# half

This program allows you to calculate your half of a restaurant bill, including tax and tip. You will need to provide the bill amount, tax percentage, and tip percentage to get the result.

## Learning Goals

This project aims to:

- Work with different data types in C
- Practice type casting
- Use math operations to calculate values
- Create a function with input parameters and return value

## Background

Suppose you are eating out at a restaurant with a friend and want to split the bill evenly. You may want to anticipate the amount you’ll owe before the bill arrives with tax added. In this problem, you’ll complete a function to calculate the amount each of you owes based on the bill amount, the tax, and the tip.

## Implementation Details

Your function should use the input parameters, bill, tax, and tip, to calculate the final amount. However, since these values are percentages, you’ll have to do some work to convert these to more appropriate formats to use for your calculation.

The tax should be added to the bill amount before calculating the tip. Finally, you will return exactly half of the full amount, including the bill amount, the tax, and the tip.

## Usage

To use this program, compile the half.c file and run the executable. Then, enter the requested information: the bill amount, the tax percentage, and the tip percentage. The program will output the amount you owe, rounded to two decimal places.

```lang-bash
$ gcc -o half half.c -lcs50
$ ./half
Bill before tax and tip: 50
Sale Tax Percent: 8.25
Tip percent: 20
You will owe $32.18 each!
```

## Code Explanation

In the main function, we ask the user to input the bill amount, tax percentage, and tip percentage using the get_float and get_int functions from the CS50 Library. Then, we call the half function with these values as arguments.

The half function calculates the amount each person owes by adding the tax and tip to the bill amount, dividing the total by two, and returning the result. Note that we need to divide the tax and tip percentages by 100 to use them in our calculation.

## Thought Question

Why do you think there are different data types in C?

Different data types in C allow us to represent different types of values and perform operations on them. For example, integers (int) can represent whole numbers, while floating-point numbers (float, double) can represent decimal numbers. Using the appropriate data type for each value in our program can help us avoid errors and make our code more efficient. Additionally, different data types have different memory requirements, and choosing the right data type can help us optimize the memory usage of our program.
