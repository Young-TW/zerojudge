# a559. NCPC PC Matrix

## 內容

Problem C

  Matrix

  Input File: pc.in

  Time limit: 5 seconds

          Given k sets, where k >= 2 and each set has n integers, they are said to be compatible if a k×n matrix B can be constructed from them to meet the following two conditions:

  l  Each row of B is constructed from a different set and is a permutation of the integers in the corresponding set.

  l  For all i and j, 1 <= i <= k-1, 1 <= j <= n, bi,j is less than bi+1,j, where bi,j is the element at the ith row and jth column of B.

  For example, consider two sets {6,3,5} and {1,4,2}. The two sets are compatible because a 2×3 matrix B can be constructed as follows to meet the above two conditions. The first row of B is from the second set and is [1 4 2], while the second row of B is from the first set and is [3 6 5].

          Now consider m (m >= 2) sets each of which has n integers. Also assume that among the m sets, at least two of them are compatible. There are many possible ways to select k (2 <= k <= m) sets from the m sets. Let kmax denote the largest number of sets which are selected from the m sets and are compatible. Your task is to write a program that computes kmax.

   

  Technical Specification

  l  The number of sets, m, is at least 2 and at most 2500. At least two of the m sets are compatible. The number of integers in each of the m sets, n, is at least 1 and at most 20. Each integer in a set is at least 1 and at most 50000.

## 輸入說明

The first line of the input file contains an integer, denoting the number of test cases to follow. For each test case, the first line contains two positive integers m and n, respectively denoting the number of sets and the number of integers in each set; in the next m lines, each line gives n integers for a set.

## 輸出說明

For each test case, output its kmax in a new line.

## 範例輸入 #1

```
2
2 3
6 3 5
1 4 2
3 2
3 1
2 4
6 5
```

## 範例輸出 #1

```
2
3
```
