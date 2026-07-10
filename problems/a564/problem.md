# a564. ITSA201205 P4 Group without direct leaders

## 內容

In X company, everyone, except the CEO, has a direct leader. There are n persons in the company and everyone has a unique ID from 0 to n-1. The ID of the CEO is 0, and the ID of any one is larger than the one of his/her direct leader. Besides everyone has a weight which is a positive integer. We want to find a group of weight as large as possible such that no one is the direct leader of any other in the group.

## 輸入說明

The input contains three lines. The first line is an integers n, 1<n<=90000, which indicates the number of persons in the company. The second line consists of n integers which are the weights of person 0,1,…, n-1, respectively. The total weight is no more than 100,000,000. In the third line, there are n-1 integers which are the ID of direct leaders of person 1, 2,…, n-1, respectively.

## 輸出說明

Output the maximum number of person we can group in one line.

## 範例輸入 #1

```
5
10 20 30 40 50
0 1 1 3
```

## 範例輸出 #1

```
90
```
