# d751. 10049 - Self­describing Sequence

## 內容

Solomon Golomb's self­describing sequence <f(1), f(2), f(3), ...> is the only non­decreasing sequence of positive integers with the property that it contains exactly f(k) occurrences of k for each k. A few moments thought reveals that the sequence must begin as follows:



![image](ShowImage?id=354)
 



In this problem you are expected to write a program that calculates the value of f(n) given the value of n.

## 輸入說明

The input may contain multiple test cases. Each test case occupies a separate line and contains an integer n ( 1 <= n <= 2,000,000,000 ). The input terminates with a test case containing a value 0 for n and this case must not be processed.

## 輸出說明

For each test case in the input output the value of f(n) on a separate line.

## 範例輸入 #1

```
100
9999
123456
1000000000
0
```

## 範例輸出 #1

```
21
356
1684
438744
```
