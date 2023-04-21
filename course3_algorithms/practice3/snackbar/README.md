# Recursive atoi

## Learning Goals

- Practice using structs
- Write a linear search algorithm

## Background

The "game" is set as if we are at the beach and want to order a number of items from the snack bar. I have a limited amount of cash and I want to get a total cost for my items before ordering. Two functions are completed:

1. First is **add_items** which will add at least the first 4 items on the Beach Burger Shack menu.
2. Then is **get_cost** which will implement a **linear search algorithm** to search for each item, and return the corresponding price.

## Implementation Details

After calling *add_items* to initialize the menu array, it will print out the menu items and their prices, prompting us to keep selecting items until we press enter without typing anything in. *add_items* adds at least the first four menu items, and *get_cost* returns the cost of each item. When I created a linear search algorithm in get_cost, I made sure that it is case insentive.

## Thought Question

Why is an array of structs a better solution here than multiple arrays?

## Answer

1. Keeps the dataset organized and easily accessible.
2. It is easily extended to more elements.
3. It is way easier to keep track of the index. Basically the struct is doing that for us.

## Linear Search Algorithms

Here are two versions of linear search algorithms.

### Basic Linear Search

This algorithm sequentially searches through an array and returns the index of the target element, if it is found. If the target element is not present in the array, the function returns -1.
Time complexity: O(n).

```lang-c
/**
 * @brief Basic linear search algorithm
 * 
 * @param arr The array to search in
 * @param n The size of the array
 * @param target The target element to search for
 * @return int The index of the target element in the array, or -1 if it is not found
 */
int linear_search(int arr[], int n, int target)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    return -1;
}
```

### Enhanced Linear Search

This algorithm is a variant of the basic linear search that can improve the average-case performance by checking multiple elements at once. This is done by comparing the target element to a sequence of elements, rather than just one at a time.
Time complexity: O(n/k), where k is the number of elements checked at once.

```lang-C
/**
 * @brief Enhanced linear search algorithm
 * 
 * @param arr The array to search in
 * @param n The size of the array
 * @param target The target element to search for
 * @param step The number of elements to check at once
 * @return int The index of the target element in the array, or -1 if it is not found
 */
int enhanced_linear_search(int arr[], int n, int target, int step)
{
    for (int i = 0; i < n; i += step)
    {
        int j = i;
        while (j < n && j < i + step)
        {
            if (arr[j] == target)
            {
                return j;
            }
            j++;
        }
    }
    return -1;
}
```
