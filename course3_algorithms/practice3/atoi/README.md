# Recursive atoi

## Learning Goals

- Deepen an understanding of strings
- Practice creating recursive functions

## Background

"Imagine that you travel back in time to the 1970’s, when the C programming language was first created. You are hired as a programmer to come up with a way to convert strings to ints. (You may have used a function just like this in Week 2, called atoi). You want to be thorough in your development process and plan to try several approaches before deciding on the most efficient."

In this problem, I start with a simple implementation of atoi that handles positive integers using loops. The implementation uses recursion: Recursive functions can be memory-intensive and are not always the best solution, but there are some problems in which using recursion can provide a simpler and more elegant solution.

## Implementation Details

In the recursive version of convert, I start with the last char and convert it into an integer value. Then I shorten the string, removing the last char, and then I recursively call convert using the shortened string as input, where the next char will be processed.

## Thought Question

Why do you need a base case whenever you create a recursive function?

## Answer

A base case is necessary in recursive functions because it sets the boundary for when the recursion should stop. Without a base case, the recursive function would keep calling itself infinitely, leading to a stack overflow error and crashing the program.
