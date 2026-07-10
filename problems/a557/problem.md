# a557. NCPC PB Integer Partition

## 內容

Problem B

  Integer Partition

  Input File: pb.in

  Time Limit: 5 seconds

   

          A new partition problem is defined as follows. Let the symbol Py,zi be the number of ways to write a positive integer y as a sum of i positive integers having the largest part no larger than z, i.e.,

  y = a1+a2+…+ai, and z >= a1 >= a2 … >= ai >= 1

  Notice that two sums differing only in the order of their summands are considered to be the same partition. For example, P25,4 = 2 (can be partitioned in two distinct ways: 4+1, 3+2) and P25,3­ = 1 (can be partitioned in one single way: 3+2).

          Please write a program to compute the number of Piy,z with given integers y, i, and z, which y may be as large as up to 500.

   

  Technical Specification

  1.    1 <= y <= 500

  2.    1 <= i <= 50

  3.    1 <= z <= 100

## 輸入說明

The first line of the input file contains one integer m(<= 5) indicating the number of test cases to following m lines, there are three integers y, i, and z.

## 輸出說明

For each test case, output Piy,z.

## 範例輸入 #1

```
5
20 4 7
100 50 51
487 18 87
492 19 89
500 19 90
```

## 範例輸出 #1

```
13
204226
7139824136004762
20430740394679891
25985433353057732
```
