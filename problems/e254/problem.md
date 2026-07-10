# e254. 公因數求和

## 內容

在 b447 裡，要求的是所有有序對 $\color{black}{(a,\ b)}$ 的最大公因數之和，如果去掉「最大」改為求所有公因數之和，當然也有良好的解法。
給定 $\color{black}{n}$ 和 $\color{black}{m}$ ，請你對所有有序對 $\color{black}{(a,\ b)}$，其中 $\color{black}{1 \le a \le n,\ 1 \le b \le m}$ ，求 $\color{black}{\sigma (\operatorname{gcd}(a,\ b))}$ 之和，即


$\color{black}{\displaystyle \sum_{i=1}^n \sum_{j=1}^m \sigma (\operatorname{gcd}(i,\ j))}$


其中，$\color{black}{\operatorname{gcd}(a,\ b)}$ 表示 $\color{black}{a}$ 和 $\color{black}{b}$ 的最大公因數，$\color{black}{\sigma(a)}$ 表示 $\color{black}{a}$ 的正因數之和。

## 輸入說明

第一行是一個正整數 $\color{black}{T (1 \le T \le 10^4)}$，代表測資筆數。


接下來  $\color{black}{T}$ 行，每行兩個正整數  $\color{black}{n (1 \le n \le 10^7)}$ 和 $\color{black}{m (1 \le m \le 10^7)}$。

## 輸出說明

對於每筆測資，輸出求和結果。

## 範例輸入 #1

```
2
3 4
10000000 10000000
```

## 範例輸出 #1

```
19
1595007865125414
```
