# f467. 10025 - The ? 1 ? 2 ? ... ? n = k problem

## 內容

?1?2? . . .?n = k ?可填入'+'或'-'給K問N最小可以是多少


Given the following formula, one can set operators ‘+’ or ‘-’ instead of each ‘?’, in order to obtain a given k
?1?2? . . .?n = k
For example: to obtain k = 12, the expression to be used will be:
- 1 + 2 + 3 + 4 + 5 + 6 - 7 = 12
with n = 7

## 輸入說明

第一行有個T代表測資數
接下來T行會有個K(0 ≤ |k| ≤ 1000000000)


The first line is the number of test cases.
Each test case of the input contains an integer k (0 ≤ |k| ≤ 1000000000).

## 輸出說明

輸出一個貌似答案的數字


For each test case, your program should print the minimal possible n (1 ≤ n) to obtain k with the above formula.

## 範例輸入 #1

```
2
12
-3646397
```

## 範例輸出 #1

```
7
2701
```
