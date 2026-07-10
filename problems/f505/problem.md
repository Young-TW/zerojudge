# f505. 10603 - Fill

## 內容

給容量分別為a,b,c的三杯水，倒法是一杯水到另一杯水倒到自己空或是別人滿為止，一開始a,b是空的c是滿的問是否能得到d的水如果不能則輸出d'(小於d最大的容量)


There are three jugs with a volume of a, b and c liters. (a, b, and c are positive integers not greater than 200). The first and the second jug are initially empty, while the third is completely filled with water. It is allowed to pour water from one jug into another until either the first one is empty or the second one is full. This operation can be performed zero, one or more times.
You are to write a program that computes the least total amount of water that needs to be poured;so that at least one of the jugs contains exactly d liters of water (d is a positive integer not greater than 200). If it is not possible to measure d liters this way your program should find a smaller amount of water d' < d which is closest to d and for which d' liters could be produced. When d' is found, your program should compute the least total amount of poured water needed to produce d' liters in at least one of the jugs.

## 輸入說明

第一行有個T代表測資數
接下來T行分別有a,b,c,d(0<a,b,c,d<200)


The first line of input contains the number of test cases. In the next T lines, T test cases follow. Each test case is given in one line of input containing four space separated integers — a, b, c and d.

## 輸出說明

輸出最少要到多少的水和d或d'


The output consists of two integers separated by a single space. The first integer equals the least total amount (the sum of all waters you pour from one jug to another) of poured water. The second integer equals d, if d liters of water could be produced by such transformations, or equals the closest smaller value d' that your program has found.

## 範例輸入 #1

```
2
2 3 4 2
96 97 199 62
```

## 範例輸出 #1

```
2 2
9859 62
```
