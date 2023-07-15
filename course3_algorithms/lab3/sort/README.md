# Sort

*Sorting Algorithm Identifier* code for week 3 lab of CS50x 2023

## Learning Goals

- Analyze three sorting programs to determine which algorithms they use.

## Background

In the lecture of week 3, a few algorithms for sorting a sequence of numbers were explained: selection sort, bubble sort, and merge sort.

- **Selection sort** iterates through the unsorted portions of a list, selecting the smallest element each time and moving it to its correct location.
- **Bubble sort** compares pairs of adjacent values one at a time and swaps them if they are in the incorrect order. This continues until the list is sorted.
- **Merge sort** recursively divides the list into two repeatedly and then merges the smaller lists back into a larger one in the correct order.

## Implementation Details

This project provides three pre-compiled C programs, sort1, sort2, and sort3, each of which implements a different sorting algorithm, namely, selection sort, bubble sort, or merge sort.
The task is to identify which sorting algorithm is used by each program by running them on different lists of values. The lists are provided in text files, which contain n lines of values either reversed, shuffled, or sorted.

The text files are run and timed. The results are recorded in *answers.txt*, along with an explanation for each program.

## How to solve

The whole point of this exercise is to be able to select the best algorithm for our use case based on [this table](https://www.bigocheatsheet.com/). Different sorting algorithms will have different complexities, different worst-case, best-case and average-case results. Also, these results will be different if the data are sorted, random or reverse-sorted. Of course it also depends on the dataset size, since in smaller datasets some differences are magnified if the algorithms have the same O-notation.

For this exercise, the algorithms are summarized in this table:

----------------------------------------------------------------------------------------
    Algorithm       |   Time Complexity                             |   Space Complexity
                    |   Best        |   Average     |   Worst       |   Worst
----------------------------------------------------------------------------------------
    Mergesort       |   Ω(nlog(n))  |   Θ(n log(n)) |   O(n log(n)) |   O(n)
    Bubble Sort     |   Ω(n)        |   Θ(n^2)      |   O(n^2)      |   O(1)
    Selection Sort  |   Ω(n^2)      |   Θ(n^2)      |   O(n^2)      |   O(1)
----------------------------------------------------------------------------------------

## Conclusion

1. For a sorted array, the fastest will be Mergesort, then Bubblesort and then Selectionsort (best case scenario).
2. For a reverse sorted array, the fastest will be Mergesort and the others will be relatively the same (worst case scenario).
3. For a random array, it is the same as before.

We can also identify mergesort by the Space complexity (it will fill up the RAM with large datasets).
After studying the code, bubblesort generally requires more swaps than selectionsort, which can make it slower in practice.
