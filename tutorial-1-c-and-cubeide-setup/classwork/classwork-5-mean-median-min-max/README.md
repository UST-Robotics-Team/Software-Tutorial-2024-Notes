[Back to Main](../../README.md)

# Classwork 5 : Mean Median Min Max

> What do mathematicians sleep on? Matrices!!

<details>

<summary>Authors</summary>

Dicaprio Cheung (dhcheungaa@connect.ust.hk)

</details>

## Problem

Use the given skeleton code to write a program to find the mean, median, min, and max of a set of numbers.

The skeleton code is separated into multiple files:
- `main.c` the main part of the code which handles the input of the set of numbers
- `mean.c` the file that calculates the mean of the set of numbers 
- `median.c` the file that calculates the median of the set of numbers 
- `min.c` the file that calculates the min of the set of numbers 
- `max.c` the file that calculates the max of the set of numbers 
- `mean.h` the header file of `mean.c`
- `median.h` the header file of `median.c`
- `min.h` the header file of `min.c`
- `max.h` the header file of `max.c`

The mean is the average value of a set of numbers.

e.g. Mean of {1, 2, 3, 3, 1, 2} = (1 + 2 + 3 + 3 + 1 + 2) / 6 = 2

The median is the number that is ranked in the middle after the array is sorted. Please refer to the following explanation for implementing sort algorithm https://www.geeksforgeeks.org/bubble-sort-algorithm/ 

e.g. median of {1, 1, 1, 1, 1, 4, 9} is 1

For arrays of even length, the median is the average of the two elements in the middle. e.g. median of {1, 1, 2, 3, 6, 7} = (2 + 3) / 2 = 2.5

The min is the smallest number in the set

The max is the biggest number in the set

#### Assumption

- There will be at most 300 numbers in the set.
- The input numbers are inside `float` range.

#### Example

The execution of the program should look like this:

```
Enter a number to append to the number set. Enter "\" to stop appending.
>1
>2
>4
>9
>0
>2
>\
Mean=3
Median=2
Min=0
Max=9
```

