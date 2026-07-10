# a556. NCPC PI Christmas Gifts

## 內容

Problem I

  Christmas Gifts

  Input File: pi.in

  Time Limit: 3 seconds

          Children always expect gifts at Christmas Eve. Every child in the community No-Common-Present-Compromise (NCPC for short) can have two wished for toys, and Santa Claus always promises at least one of the two wishes. Children in NCPC are all unselfish such that a toy can be shared by many children. This year, all the wished have been collected and you are asked to help Santa Claus to prepare the gifts for all the children. Due to the limited capacity of the cart, you need to minimize the number of gifts. But remember, for every child, at least one of the two wishes should be satisfied.

          For the example shown in the first test case of the Sample Input, there are four children. The first child wished to have toy 0 or 1, and the toys wished by the other three children are respectively 100 or 1, 100 or 0, and 100 or 200. For this case, you can prepare only two toys (0 and 100) to satisfy all the four children.

   

  Technical Specification

  1.     Every wish is a toy and labeled by an nonnegative integer at most 10000.

  2.     The number n of different toys is at most 250.

  3.     The number m of children is a positive integer and at most 5000.

  4.     For each test case, n <= 100 or m<= 400.

## 輸入說明

The input file contains several test cases. For each test case, the first line contains the integer m which is the number of children in this case. In the following m lines, each line contains two integers separated by a space, in which the two integers are the toy labels the child wishes for. A case with m = 0 indicates the end of the input and you don’t need to process it.

## 輸出說明

For each test case, output in one line the minimum number of gifts that Santa Claus should prepare.

## 範例輸入 #1

```
4
0 1
100 1
100 0
100 200
12
10 20
20 30
30 40
40 50
50 60
60 70
70 80
80 10
10 0
30 0
50 0
70 0
0
```

## 範例輸出 #1

```
2
4
```
