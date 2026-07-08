# b607. Number Partition

## 內容

A natural number that is greater than one can be partitioned as a sum of some prime number(s). Your task is to find out as few primes as possible that sum up to the natural number. If the number of such partitions is more than one, only the partition with greatest product of those summands is considered.


大於1的自然數可以被分解為數個質數的和。 你的任務是找出盡可能少的質數，總和出該自然數。 如果分解的方法多於一組，就輸出質數相乘結果最大的那個分解。

## 輸入說明

Each test case will contains a natural number n, 2 <= n <= 1000000. Input is terminated by a case where the value of n is zero. This case should not be processed.


每一組測試資料 n 範圍為 2 <= n <= 1000000, 當讀入 n=0 時程式結束

## 輸出說明

The input data consists of several test cases. For each test case, output a single line which contains the number of summands and also all summands, separated by a space.
The summands for each test case should be listed in non-decreasing order.


每一組輸出資料第一個數字為分解後的質數個數，然後依漸增的數列輸出每個質數, 中間用空白隔開

## 範例輸入 #1

```
49
6
12
0
```

## 範例輸出 #1

```
2 2 47
2 3 3
2 5 7
```
