# Seven Day Averages

## Learning Goals

- Work with live data
- Get practice with CSV files and csv.DictReader
- Practice using dictionaries, lists and exceptions

## Background

A popular way to track COVID cases is using a 7-day average. Some states only record cases once a week, so using a 7-day average is much more accurate than daily numbers. In this program, you will be using a New York Times repository of live, cumulative COVID data to calculate new daily cases, create a 7-day average, and compare this week’s average to the previous week.

## Implementation Details

The distribution code for this problem uses the python **requests library** to access the New York Times data stored in an accessible GitHub repository. This is stored as a **CSV file**. The program then uses DictReader to read the CSV file. It then creates a states list to use selected states for calculations.

The main functions of the implementation are *calculate* and *comparative_averages*.

### calculate

In calculate, you’ll be creating a dictionary, new_cases, which will keep track of 14 days of new COVID cases for each state. Keys in this dict will be the names of states, and the values for each of those keys will be the most recent 14 days of new cases. Since the data from the New York Times is cumulative, each day’s new cases must be calculated by subtracting the previous day’s cases. To do this, you may want to create a second dictionary, previous_cases, that keeps track of each day’s new cases as it’s calculated.

### comparative_averages

Since your new_cases dictionary is passed to this function, you can calculate this week’s 7-day average by summing up the last 7 elements in the list for a selected state, then dividing this by 7. You can create a 7-day average for the previous week by doing the same with the first 7 elements in that same list.
The calculation of the percent increase or decrease is being done by taking the difference of the two 7-day averages and dividing by last week’s average.

### extra

In order to detect division by zero by handling, a ZeroDivisionError with a try and except block is used:

```lang-python
try:
    numerator / denominator
except ZeroDivisionError:
    ...
```
