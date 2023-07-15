# Recursive atoi

## Learning Goals

- Pass an array into a function
- Create a helper function that finds a maximum value

## Background

There are many situations where someone finds it helpful to have a function that finds the maximum (and minimum) value in an array. Since there is no built-in max function in C, I create one in this practice problem.

## Implementation Details

The main function initializes the array, asks the user to enter values, and then passes the array and the number of items to the max function. The max function iterats through every element in the array, and returns the maximum value.

## Thought Question

What types of programs might benefit from a max helper function?

## Answer

1. **Data analysis programs**: When analyzing large datasets, it is often useful to find the maximum value of a specific variable. The max() function can be used to find the maximum value of a numerical variable in an array or list.
2. **Gaming programs**: In games, it is often necessary to keep track of the maximum score achieved by a player. The max() function can be used to find the maximum score from an array of scores.
3. **Financial programs**: Financial programs often need to find the highest value of a stock price over a given time period. The max() function can be used to find the maximum value of a stock price array.
4. **Engineering programs**: In engineering, it is often necessary to find the maximum value of a signal over a given time period. The max() function can be used to find the maximum value of a signal array.
