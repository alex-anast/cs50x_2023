# Recursive atoi

## Learning Goals

- Practice working with **structs**
- Practice applying **sorting algorithms**

## Background

We seem to be breaking records every year for the hottest weather ever recorded. Climate scientists keep track of what are called “new normals” over multiple years so that we can better predict and prepare for conditions in the near future. The official normals are calculated for a uniform 30 year period, and consist of annual/seasonal, monthly, daily, and hourly averages and statistics of temperature, precipitation, and other climatological variables from almost 15,000 U.S. weather stations.

July is the hottest month of the year for most large US cities. Daytime temperatures above 80 degrees Fahrenheit regularly occur nearly everywhere. The exceptions are some cities along the Pacific coast.

In this problem, I sort the average high temperature values for 10 cities, in decending order.

## Implementation Details

The main function initializes the temps array, calls the sort_cities function and prints out the array in sorted order. I was supposed to use an O(n2) sorting algorithm of my choice (bubble sort, selection sort, or insertion sort) to sort the array by temperature, in descending order.

I personally did it with all the three, for practice.

## Thought Question

Which of the sorting algorithms did I choose and why?
A better question would be, what are the parameters of choosing the best algorithm for my case?

## Answer

1. Ease of use and how fast I can type it as a programmer
2. Limitations of time and space
3. Even if all the algorithms written are 0(n^2), there are still differences, especially in small data sets.

## Compare Bubblesort, Selection Sort and Insertion Sort

> ### Bubble Sort

Bubble Sort is a simple algorithm that works by repeatedly swapping adjacent elements that are in the wrong order. It is called "bubble sort" because elements "bubble" to the top of the list. The algorithm loops through the list, compares adjacent elements, and swaps them if they are in the wrong order. The loop continues until no more swaps are necessary.

Bubble Sort is easy to understand and implement, but it is not very efficient. Its worst-case and average-case time complexity is O(n^2), which means it is not suitable for large datasets. Bubble Sort is useful only for small datasets or when simplicity is more important than efficiency.

> ### Selection Sort

Selection Sort is another simple algorithm that works by repeatedly selecting the smallest element from the unsorted portion of the list and swapping it with the first element of the unsorted portion. The algorithm loops through the list, finds the smallest element, and swaps it with the first element. The loop then moves on to the next element and repeats the process.

Selection Sort is also easy to understand and implement, but it is slightly more efficient than Bubble Sort. Its worst-case and average-case time complexity is O(n^2), which means it is still not suitable for large datasets. Selection Sort is useful only for small datasets or when simplicity is more important than efficiency.

> ### Insertion Sort

Insertion Sort is a more efficient algorithm that works by dividing the list into two parts: a sorted part and an unsorted part. The algorithm loops through the unsorted part of the list, picks one element at a time, and inserts it into the correct position in the sorted part of the list. The algorithm repeats until the entire list is sorted.

Insertion Sort is more efficient than Bubble Sort and Selection Sort because it requires fewer comparisons and swaps. Its worst-case time complexity is O(n^2), but its average-case time complexity is O(nlogn), making it suitable for small to medium-sized datasets. Insertion Sort is useful when the list is almost sorted, as it requires fewer comparisons and swaps than other algorithms.

> ### Comparison

- Bubble Sort, Selection Sort, and Insertion Sort are all simple sorting algorithms that are easy to understand and implement.
- Bubble Sort and Selection Sort have a worst-case and average-case time complexity of O(n^2), while Insertion Sort has a worst-case time complexity of O(n^2) and an average-case time complexity of O(nlogn).
- Bubble Sort and Selection Sort are not suitable for large datasets, while Insertion Sort is suitable for small to medium-sized datasets.
- Insertion Sort is more efficient than Bubble Sort and Selection Sort because it requires fewer comparisons and swaps.
- Bubble Sort and Selection Sort are useful when simplicity is more important than efficiency, while Insertion Sort is useful when efficiency is more important than simplicity.

> ### Conclusion

In summary, while Bubble Sort and Selection Sort are simple and easy to understand, they are not very efficient and are only suitable for small datasets. Insertion Sort, on the other hand, is more efficient and is suitable for small to medium-sized datasets. Ultimately, **the choice of algorithm will depend on the specific requirements of the task at hand, including the size of the dataset, the expected performance, and the complexity of the implementation**.
