# b606. Add All

## 內容

給你一個數列, 找出數列上數字相加時最好的成本是多少



The problem name reﬂects your task; just add a set of numbers. But you may feel yourselves condescended, to write a program just to add a set of numbers. Such a problem will simply question your erudition. So, let us add some ﬂavor of ingenuity to it.


Addition operation requires cost now, and the cost is the summation of those two tobe added. So, to add 1 and 10, you need a cost of 11. If you want to add 1, 2 and 3.


There are three ways: 


(1) 1 + 2 = 3, cost = 3; 3 + 3 = 6, cost = 6; Total = 9
(2) 1 + 3 = 4, cost = 4; 4 + 2 = 6, cost = 6; Total = 10
(3) 2 + 3 = 5, cost = 5; 5 + 1 = 6, cost = 6; Total = 11


Your task is write a program to add a set of integers so that the cost is minimized.

## 輸入說明

同一個輸入檔有多筆測試資料
每筆測試資料有兩行, 第一行是數列長度, 第二行是數列, 數列不一定排序過, 也可能會有重複數字

Each test case will start with a positive number n, 2 <= n <= 5000, and followed by n  positive integers ki, ki< 100000. Input is terminated by a case where the value of n is zero. This case should not be processed.

## 輸出說明

For each case, output the minimum total cost of addition in a single line.

## 範例輸入 #1

```
3
1 2 3
4
1 2 3 4
5
10 5 7 13 11
0
```

## 範例輸出 #1

```
9
19
104
```
