# prime

## Learning Goals

- Practice using for loops
- Using modulo
- Creating a Boolean function

## Background

Prime numbers are whole numbers greater than 1 whose only factors are 1 and itself. For instance, 3 is a prime number because its only factors are 1 and 3. On the other hand, 4 is not a prime number because it is the product of 2 × 2. In this practice, you will write an algorithm to generate all prime numbers in a range specified by the user.

## Implementation Details

One way to check if a number is prime is to try dividing it by every number from 2 up to, but not including, the number itself. If any number divides into it with no remainder, that number is not prime.

The main function in the code above contains a for loop that iterates through the range specified by the user, with both ends inclusive. For instance, if the user types in 1 for min and 100 for max, the for loop will test each number, 1 to 100. Each of these numbers is passed to a function, prime, that you will implement to return either true or false depending on whether the number is prime.

To implement the prime function, there is another for loop that iterates through each number from 2 up to the square root of the input number. **This is more efficient than checking if a number is divisible by every number between 2 and 1 less than itself**. If any of these numbers divides the input number with no remainder, the number is not prime and the function returns false.

## Thought Question

There are different ways to generate prime numbers more efficiently than checking if a number is divisible by every number between 2 and 1 less than itself. One example is the Sieve of Eratosthenes, which involves creating a list of numbers from 2 to a certain limit, and crossing off multiples of each prime number until only primes remain.
