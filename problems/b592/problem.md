# b592. The Tower of Hanoi

## 內容

The Tower of Hanoi problem is a popular one in computer science. Brieﬂy speaking, the problem is to transfer all the disks from peg-A to peg-C using peg-B as intermediate one in such a way that at no stage a larger disk is above a smaller disk. The minimum number of moves is required for this task.


It is so well studied that one can find the sequence of moves for smaller number of disks such as 3 or 4. A trivial computer program can find the case of large number of disks also. Here we have made your task little bit difcult by making the problem more ﬂexible. Here the disks can be placed in any peg initially.


If more than one disk is in a certain peg, then they will be in a valid arrangement (larger disk will not be on smaller ones). We will give you two such arrangements of disks. Your task is to find out the minimum number of moves which will transform the first arrangement into the second one. Of course you always have to maintain the constraint that smaller disks must be upon the larger ones.

## 輸入說明

The input data consists of several test cases. Each test case contains three lines.


The first line contains a positive number n, 1 <= n <= 30, which denotes the number of disks. The two arrangements are denoted by the next two lines. Each arrangement will be represented by n integers. The value of integer is 1, 2 or 3, which denote the disk is placed in peg-A, peg-B and peg-C respectively. For example, if the i-th (1 <= i <= n) integer is 1, the i-th disk is in peg-A. The figure shown below is an example of test case. It can be described as follows and the minimum number of moves is 6.


4
1 1 1 1
1 2 2 1

![image](ShowImage?id=881)
Input is terminated by a case where the value of n is zero. This case should not be processed.

## 輸出說明

For each test case, output the minimum number of moves as specified in the problem statement.

## 範例輸入 #1

```
4
1 1 1 1
1 2 2 1
3
1 1 1
2 2 2
3
1 2 3
3 2 1
4
1 1 1 1
1 1 1 1
0
```

## 範例輸出 #1

```
6
7
3
0
```
