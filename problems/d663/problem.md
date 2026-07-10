# d663. 11730 - Number Transformation

## 內容

You are given an integer number S. You can transform any integer number A to another integer number B by adding x to A. This x is an integer number which is a prime factor of A (Please note that 1 and A are not being considered as a factor of A). Now, your task is to find the minimum number of transformations required to transform S to another integer number T.

給你一個數字S，你可以將A轉換成B藉由加上一個X，X是一個A的質因數(1跟A不考慮進去)，現在你的工作就是找出最少需要轉換次數把S轉換成T

EX: 6 12

6->9->12   2次

6->8-> 10->12 3次

## 輸入說明

For each test case, there will be a line with two integers, S (1<=S<=100) & T (1<=T<=1000), as described above. The last test case will be followed by a line with two 0 s denoting end of output. This case should not be processed.

每組測資都有兩的數字S (1<=S<=100) & T (1<=T<=1000)，

兩個0代表結束，不用輸出任何數字 。

## 輸出說明

For every test case except the last one, print a line of the form “Case X: Y” where X is the serial number of output (starting from 1). Y is the minimum number of transformations required to transform S to T. If it is not possible to make T from S with the given rules, Y shall be -1.

對於每個一個測資，除了0 0以外 ，請應出 “Case X: Y”，X從1開始算起，Y為S轉換到T的最小次數，若是無法轉換成功請書出-1

## 範例輸入 #1

```
6 12
6 13
0 0
```

## 範例輸出 #1

```
Case 1: 2
Case 2: -1
```
