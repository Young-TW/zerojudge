# e182. 框架區間 (加強版)

## 內容

基因是含有特定遺傳信息的結構,用來決定生物的種性特徵。


生物學家發現,與特定功能相關的一群基因在基因序列上的位置通常十分靠近, 因此在基因序列中的連續片段被認為是有意義的。


一個包含 $\color{black}{n}$ 個基因的序列可以用 $\color{black}{\{1,\ 2,\ \cdots,\ n\}}$ 所組成的排列 $\color{black}{S=(s_1,\ s_2,\ \cdots,\ s_n)}$ 來表示。


為了預測基因序列 $\color{black}{S}$ 上可能有意義的片段,一位生物學家遭遇了下列問題。


令 $\color{black}{F(a,\ b)}$ 代表在基因序列 $\color{black}{S}$ 上位置落在基因 $\color{black}{a}$ 和基因 $\color{black}{b}$ 之間的所有整數所構成的集合 (含 $\color{black}{a}$ 和 $\color{black}{b}$)。


例如，令 $\color{black}{S = (2,\ 7,\ 6,\ 4,\ 14,\ 13,\ 5,\ 8,\ 1,\ 9,\ 11,\ 10,\ 12,\ 3)}$，


則 $\color{black}{F(6,\ 8) = F(8,\ 6) = \{6,\ 4,\ 14,\ 13,\ 5,\ 8\}}$。


令 $\color{black}{I(a,\ b)}$ 代表數線上 $\color{black}{a}$ 和 $\color{black}{b}$ 這兩個整數間所有整數所構成的集合 (含 $\color{black}{a}$ 和 $\color{black}{b}$)。


例如，$\color{black}{I(6,\ 8) = I(8,\ 6) = \{6,\ 7,\ 8\}}$。在基因序列 $\color{black}{S}$ 上如果兩個整數 $\color{black}{a}$ 和 $\color{black}{b}$ ， $\color{black}{1 \le a < b \le n}$，


滿足 $\color{black}{F(a,\ b) = I(a,\ b)}$ 則稱 $\color{black}{(a,\ b)}$ 構成一個「框架區間」 (framed interval)。


舉例來說, 考慮基因序列 $\color{black}{S = (2,\ 7,\ 6,\ 4,\ 14,\ 13,\ 5,\ 8,\ 1,\ 9,\ 11,\ 10,\ 12,\ 3)}$，以 $\color{black}{(a,\ b) = (9,\ 12)}$ 為例，


因為 $\color{black}{F(9,\ 12) = \{9,\ 11,\ 10,\ 12\} = \{9,\ 10,\ 11,\ 12\}= I(9,\ 12)}$，所以 $\color{black}{(9,\ 12)}$ 是一個框架區間。


相同的 $\color{black}{(6,\ 7)}$、$\color{black}{(10,\ 11)}$ 和 $\color{black}{(13,\ 14)}$ 也是框架區間。



這位生物學家想知道給定一個基因序列 $\color{black}{S}$，有多少數對 $\color{black}{(a,\ b)}$， $\color{black}{1 \le a < b \le n}$，是一個框架區間?


例如，在基因序列 $\color{black}{S = (2,\ 1,\ 5,\ 4,\ 3)}$ 上，是框架區間的數對 $\color{black}{(a,\ b)}$，$\color{black}{1 \le a < b \le 5}$，


有 $\color{black}{(1,\ 2)}$、$\color{black}{(3,\ 4)}$、$\color{black}{(3,\ 5)}$ 和 $\color{black}{(4,\ 5)}$，共四個。

## 輸入說明

第一行有一整數 $\color{black}{T}$，代表有 $\color{black}{T}$ 組測試資料。


接下來每兩行用來描述一組基因序列，
第一行有一整數 $\color{black}{n}$，第二行有 $\color{black}{n}$ 個整數 $\color{black}{s_1,\ s_2,\ \cdots,\ s_n}$ (數字之間以一個空白隔開)，


代表基因序列 $\color{black}{S = (s_1,\ s_2, \cdots,\ s_n)}$，任兩個數字都不相同且 $\color{black}{1 \le s_1,\ s_2,\ \cdots,\ s_n \le n}$。

## 輸出說明

針對所輸入的基因序列 $\color{black}{S}$，輸出一個數字，代表有多少數對 $\color{black}{(a,\ b)}$， $\color{black}{1 \le a < b \le n}$，是一個框架區間?

## 範例輸入 #1

```
輸入範例 1:
3
4
3 1 4 2
4
3 2 1 4
5
2 1 5 4 3

輸入範例 2:
2
14
2 7 6 4 14 13 5 8 1 9 11 10 12 3
11
3 10 4 5 6 8 7 9 11 2 1
```

## 範例輸出 #1

```
輸出範例 1:
0
3
4

輸出範例 2:
4
9
```
