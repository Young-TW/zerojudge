# h999. 線上外賣學習

## 內容

$\text{Waimai}$ 的班上有人確診了，於是 $\text{Waimai}$ 要居家隔離。


總共要隔離 $n$ 天，每天 $\text{Waimai}$ 都可以叫外賣。今天要吃什麼呢？$\text{Waimai}$ 有 $m + 1$ 種選擇，他可以從 $m$ 種食物裡選第 $i$ 種，且飽足度為 $a_i$，或是可以什麼都不選，飽足度為 $0$。


經過 $n$ 天後，$\text{Waimai}$ 最後的總飽足度為 $1\sim n$ 天飽足度的加總。$\text{Waimai}$ 想知道他的總飽足度為 $0\sim k$ 分別的方法數。假設 $cnt_i$ 為讓總飽足度為 $i$ 的方法數對 $998244353$ 取餘數，請輸出 $cnt_0 \oplus cnt_1 \oplus \dots \oplus cnt_k$，其中 $\oplus$ 為 $\text{bitwise xor}$。

## 輸入說明

第一行有兩個正整數 $n, m, k$，代表要隔離幾天、每天有幾種外賣可以選，和 $\text{Waimai}$ 想知道他的總飽足度為 $0\sim k$ 分別的方法數。


第二行有 $m$ 個數字 $a_1 \sim a_m$，代表每個外賣的飽足度。


- $1 \leq n \leq 10^{10^5}$
- $1 \leq m, k \leq 2\times 10^5$
- $1 \leq a_i \leq k$

## 輸出說明

請輸出一個整數，代表 $cnt_0 \oplus cnt_1 \oplus \dots \oplus cnt_k$。

## 範例輸入 #1

```
2 2 3
2 1
```

## 範例輸出 #1

```
2
```
