# e209. C(n, k) Again!

## 內容

令 $\color{black}{n,\ k\ (k \le n)}$ 為非負整數，定義 $\color{black}{\displaystyle C^n_k = \frac{n!}{k!(n-k)!}}$，很顯然地，我們可以從組合意義上得知 $\color{black}{C^n_k}$ 也是整數。


想要證明 $\color{black}{\displaystyle \frac{n!}{k!(n-k)!}}$ 是整數，不妨提出 $\color{black}{(n-k)!}$ ，改為證明任意連續 $\color{black}{k}$ 個非負整數的乘積皆能被 $\color{black}{k!}$ 整除。


現在有兩個大小為 $\color{black}{k}$ 的集合 $\color{black}{S = \{x | x \in \mathbb{N},\ 1 \le x \le k\},\ T = \{y | y \in \mathbb{N},\ m \le y \le m + k - 1\}}$。


請在 $\color{black}{S,\ T}$ 間建立若干條「邊」，滿足下列性質：


1. 權重大於 1。


2. 對於所有 $\color{black}{x \in S}$， 其連接的邊權重乘積(沒有邊視為 1)恰為 $\color{black}{x}$ 。


3. 對於所有 $\color{black}{y \in T}$， 其連接的邊權重乘積(沒有邊視為 1)為 $\color{black}{y}$ 的因數。



![image](ShowImage?id=1318)

## 輸入說明

兩個正整數 $\color{black}{m,\ k (m \le 10^9,\ k \le 10^6)}$。

## 輸出說明

輸出共有 $\color{black}{k}$ 行。


第 $\color{black}{x}$ 行首先輸出一個非負整數 $\color{black}{d}$，代表 $\color{black}{x(x \in S)}$ 連接 $\color{black}{d}$ 條邊，接著輸出 $\color{black}{d}$ 個數對 $\color{black}{y\ w}$，表示 $\color{black}{x}$ 和 $\color{black}{y \in T}$ 有一條權重為 $\color{black}{w}$ 的邊。數字以空格隔開，行尾不應有多餘空白。

## 範例輸入 #1

```
範例輸入 1:
5 4

範例輸入 2:
5 4

範例輸入 3:
1 4
```

## 範例輸出 #1

```
範例輸出 1:
0
1 6 2
1 6 3
1 8 4

範例輸出 2:
0
1 8 2
1 6 3
2 6 2 8 2

範例輸出 3:
0
1 2 2
1 3 3
1 4 4
```
