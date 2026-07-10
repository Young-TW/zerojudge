# a146. Sliding Window

## 內容

An array of size n ≤ 106 is given to you. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves rightwards by one position. Following is an example: 
The array is [1 3 -1 -3 5 3 6 7], and k is 3.Window positionMinimum valueMaximum value[1  3  -1] -3  5  3  6  7 -13 1 [3  -1  -3] 5  3  6  7 -33 1  3 [-1  -3  5] 3  6  7 -35 1  3  -1 [-3  5  3] 6  7 -35 1  3  -1  -3 [5  3  6] 7 36 1  3  -1  -3  5 [3  6  7]37Your task is to determine the maximum and minimum values in the sliding window at each position.

## 輸入說明

The input consists of two lines. The first line contains two integers n and k which are the lengths of the array and the sliding window. There are n integers in the second line.

## 輸出說明

There are two lines in the output. The first line gives the minimum  values in the window at each position, from left to right, respectively.  The second line gives the maximum values.

## 範例輸入 #1

```
8 3
1 3 -1 -3 5 3 6 7
7 3
10 -26 89 80 27 84 73
```

## 範例輸出 #1

```
-1 -3 -3 -3 3 3
3 3 5 5 6 7
-26 -26 27 27 27
89 89 89 84 84
```
