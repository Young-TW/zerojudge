# c819. gcd(Fm, Fn) 之求和問題

## 內容

定義費氏數列 $\color{black}{F_1 = F_2 = 1,\ F_n = F_{n-2} + F_{n-1}\ \forall\ n > 2}$。


給定 $\color{black}{n,\ m}$ ，你能求出 $\color{black}{\operatorname{gcd}(F_m, F_n)}$ 的值嗎？


現在有個更加複雜的問題，請你對所有有序對 $\color{black}{(a,\ b)}$，其中 $\color{black}{1 \le a \le n,\ 1 \le b \le m}$ ，求 $\color{black}{\operatorname{gcd}(F_a,\ F_b)}$ 之和，即


$\color{black}{\displaystyle \sum_{i=1}^n \sum_{j=1}^m \operatorname{gcd}(F_i,\ F_j)}$

## 輸入說明

第一行是兩個正整數 $\color{black}{C (1 \le C \le 10^7),\ T (1 \le T \le 10^4)}$，代表 $\color{black}{n,\ m}$ 的上限和測資筆數。


接下來  $\color{black}{T}$ 行，每行兩個正整數  $\color{black}{n (1 \le n \le C)}$ 和 $\color{black}{m (1 \le m \le C)}$。

## 輸出說明

對於每筆測資，輸出求和結果，請對 1000000007 取模再輸出。

## 範例輸入 #1

```
1000 2
3 4
1000 1000
```

## 範例輸出 #1

```
13
542559755
```
