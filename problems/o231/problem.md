# o231. 11340 - Newspaper

## 內容

新聞機構根據一些規則為文章支付報酬。每個字符都有其自身的價值（某些字符的價值可能為零）。作者的報酬是文章中所有字符價值的總和。你需要確定新聞機構必須支付給作者的金額。

## 輸入說明

第一行包含一個整數 N (0 < N ≤ 5)，表示測試次數。每個測試描述一個整數 K (0 < K ≤ 100)，表示有價值的字符數量。在接下來的 K 行中，有一個支付字符及其價值的表格（字符價值以美分為單位）。如果在表格中找不到字符，則其價值為零。接下來是一個整數 M (0 < M ≤ 150000)。接下來的 M 行包含文章本身。

## 輸出說明

對於每個測試，輸出新聞機構必須為文章支付的金額，格式為 ‘x.yy$’，其中 x 是沒有前導零的美元數，yy 是帶有一個前導零的美分數。

## 範例輸入 #1

```
1
7
a 3
W 10
A 100
, 10
k 7
. 3
I 13
7
ACM International Collegiate Programming Contest (abbreviated
as ACM-ICPC or just ICPC) is an annual multi-tiered competition
among the universities of the world. The ICPC challenges students
to set ever higher standards of excellence for themselves
through competition that rewards team work, problem analysis,
and rapid software development.
From Wikipedia.
```

## 範例輸出 #1

```
3.74$
```
