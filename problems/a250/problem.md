# a250. NCPC2011 Problem H Special Subsequences

## 內容

Problem H

  Special Subsequences

  Input File: ph.in

  Time Limit: 5 seconds

          Given a sequence of n integers x1,x2, …, xn and an integer k, 1≦k≦n,
we want to know if there exists a consecutive subsequence xi ,xi+1, …, xj for 
some i and j, 1≦i≦j≦n, such that the sum

![image](ShowImage?id=70)

  Is divisible by k or not.

          For example, let n = 7 and k = 6. In the sequence of 7 integers.

  2,5,1,-4,5,9,3

  The sum of the following consecutive subsequences can be divisible by k = 6.

  1.         i = 2, j = 3: 5+1 = 6,

  2.         i = 1, j = 6: 2+5+1-4+5+9 = 18,

  3.         i = 6, j = 7: 9+3 = 12,

  We are going to write a very efficient program to solve the problem with
large numver of integers in a short span of time. It is required to print only
one particular solution, not all solutions. The solution we want to print is the
first such subsequence. The first solution is the one with the smallest value
 of i. In the above example, the answer we want is i = 1 and j = 6. If there
 are more than one solution with the same value of i, we want the one with
 smallest valu of j.

## 輸入說明

An instance of the problem consists of

  1.         the number of integers n,

  2.         the sequence of integer xi , 1 ≦i≦n, and

  3.         the divisor k.

  These data are stored in 
![image](ShowImage?id=71)
+2 lines in the input file.

  1.         The first line is the integer n.

  2.         The following is  
![image](ShowImage?id=72)
 lines are the n integers xi , 1≦i≦n. Each line
contains at most 20 integers.

  3.         The last line is the integer k.

  In this problem, we assume that 1≦ n ≦100000, and -230 ≦ xi ≦ 230.

      Note that the test data file may contain more than one instances. The last
instance is followed by a line containing a single 0.

在此將題目修改 1 ≦ k ≦ 2147483647, 並且將所有數字排在同一行並不會切割

## 輸出說明

The outputs for each test case are the two integers i and j which are the indexes of
the consecutive subsequence whose sum is divisible by k. Print exactly one space
between i and j. If there are no solution print “no solutions.”

## 範例輸入 #1

```
7
2 5 1 -4 5 9 3
6
10
11 -3 1 13 -5 6 1 -8 -4 5
10
0
```

## 範例輸出 #1

```
1 6
5 9
```
