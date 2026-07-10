# f508. 12041 - BFS (Binary Fibonacci String)

## 內容

定義一個序列BFS，BFS(0)="0"，BFS(1)="1"，BFS(n)=BFS(n-2)+BFS(n-1)(加號代表連接)(n>1)
求出第N項的第L個字元到第R個字元(含L、R)


We are familiar with the Fibonacci sequence (1, 1, 2, 3, 5, 8, ...). What if we define a similar sequence for strings? Sounds interesting? Let’s see.
We define the follwing sequence:
BFS(0) = 0 BFS(1) = 1 (here “0” and “1” are strings, not simply the numerical digit, 0 or 1)for all (n > 1) BF S(n) = BF S(n − 2) + BF S(n − 1) (here, ‘+’ denotes the string concatenation operation). (i.e. the n-th string in this sequence is a concatenation of a previous two strings).
So, the first few strings of this sequence are: 0, 1, 01, 101, 01101, and so on.
Your task is to find the N-th string of the sequence and print all of its characters from the i-th to j-th position, inclusive. (All of N, i, j are 0-based indices)

## 輸入說明

第一行T代表有幾筆測資(T<=100)
接下來T行每行有三個數字N、L、R(0<=N、L、R<2^31)(L<=R且R−L<=10000)


The first line of the input file contains an integer T (T ≤ 100) which denotes the total number of test cases. The description of each test case is given below:
Three integers N, i, j (0 ≤ N, i, j ≤ 2^31 − 1) and (i ≤ j and j − i ≤ 10000). You can assume that,both i and j will be valid indices (i.e. 0 ≤ i, j < length of BFS(N)).

## 輸出說明

輸出第L個字元到第R個字元(含L、R)


For each test case, print the substring from the i-th to the j-th position of BF S(N) in a single line.

## 範例輸入 #1

```
3
3 1 2
1 0 0
9 5 12
```

## 範例輸出 #1

```
01
1
10101101
```
