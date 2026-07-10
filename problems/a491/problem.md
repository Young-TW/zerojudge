# a491. 貨物集中問題

## 內容

一個矩形平面大型倉儲空間，共有 $\color{black}{R\times C}$ 個分區，其中 $\color{black}{R}$ 代表矩形的列數，$\color{black}{C}$ 代表矩形的行數。此倉儲空間以一 $\color{black}{R\times C}$ 二維矩陣表示，倉儲空間中的每一分區以二維座標表示，二維矩陣中每一分區的內容代表各分區的儲存貨物量。今因整個倉儲空間保養維修的因素，需將所有分區的貨物暫時集中於某一分區內，並假設任一分區的容量均可以容納目前倉儲空間中的總貨物容量。因為貨物移動需要移動成本，假定一個單位的貨物從現在的分區移動到相鄰上下左右任意一個分區的成本為 $\color{black}{100}$ 元，請寫一程式決定貨物應該集中於哪一分區，其整體移動成本為最小。

## 輸入說明

$\color{black}{N}$


$\color{black}{R_1}$ $\color{black}{C_1}$


$\color{black}{A_{1, 1, 1}}$ $\color{black}{A_{1, 1, 2}}$ $\color{black}{\ldots}$ $\color{black}{A_{1, 1, C_1}}$


$\color{black}{A_{1, 2, 1}}$ $\color{black}{A_{1, 2, 2}}$ $\color{black}{\ldots}$ $\color{black}{A_{1, 2, C_1}}$


$\color{black}{\vdots}$


$\color{black}{A_{1, R_1, 1}}$ $\color{black}{A_{1, R_1, 2}}$ $\color{black}{\ldots}$ $\color{black}{A_{1, R_1, C_1}}$


$\color{black}{R_2}$ $\color{black}{C_2}$


$\color{black}{A_{2, 1, 1}}$ $\color{black}{A_{2, 1, 2}}$ $\color{black}{\ldots}$ $\color{black}{A_{2, 1, C_2}}$


$\color{black}{A_{2, 2, 1}}$ $\color{black}{A_{2, 2, 2}}$ $\color{black}{\ldots}$ $\color{black}{A_{2, 2, C_2}}$


$\color{black}{\vdots}$


$\color{black}{A_{2, R_2, 1}}$ $\color{black}{A_{2, R_2, 2}}$ $\color{black}{\ldots}$ $\color{black}{A_{2, R_2, C_2}}$


$\color{black}{\vdots}$


$\color{black}{R_N}$ $\color{black}{C_N}$


$\color{black}{A_{N, 1, 1}}$ $\color{black}{A_{N, 1, 2}}$ $\color{black}{\ldots}$ $\color{black}{A_{N, 1, C_N}}$


$\color{black}{A_{N, 2, 1}}$ $\color{black}{A_{N, 2, 2}}$ $\color{black}{\ldots}$ $\color{black}{A_{N, 2, C_N}}$


$\color{black}{\vdots}$


$\color{black}{A_{N, R_N, 1}}$ $\color{black}{A_{N, R_N, 2}}$ $\color{black}{\ldots}$ $\color{black}{A_{N, R_N, C_N}}$



- $\color{black}{N}$ 代表測試資料的筆數。
- $\color{black}{R_i, C_i}$ 代表第 $\color{black}{i}$ 筆測試資料的矩陣大小為 $\color{black}{R_i\times C_i}$。
- $\color{black}{A_{i, j, k}}$ 代表第 $\color{black}{i}$ 筆測試資料的矩陣 $\color{black}{(j, k)}$ 位置的值。
- $\color{black}{1\le N\le10}$。
- 對於所有的 $\color{black}{i \in \{1, 2, \ldots, N\}}$，均有 $\color{black}{1\le R_i, C_i\le 2000}$。
- 對於所有的 $\color{black}{i \in \{1, 2, \ldots, N\}, j \in \{1, 2, \ldots, R_i\}, k \in \{1, 2, \ldots, C_i\}}$，均有 $\color{black}{0\le A_{i, j, k}\le10^5}$。
- 輸入的數皆為整數。

## 輸出說明

$\color{black}{i_1^*}$ $\color{black}{j_1^*}$


$\color{black}{P_1}$


$\color{black}{i_2^*}$ $\color{black}{j_2^*}$


$\color{black}{P_2}$


$\color{black}{\vdots}$


$\color{black}{i_N^*}$ $\color{black}{j_N^*}$


$\color{black}{P_N}$



- $\color{black}{i_k^*, j_k^*}$ 為兩整數，代表第 $\color{black}{k}$ 筆測試資料中的貨物應集中於 $\color{black}{(i_k^*, j_k^*)}$ 分區。如有多個符合條件的 $\color{black}{(i_k^*, j_k^*)}$，請輸出字典順序最小的那組。
- $\color{black}{P_k}$ 為一整數，代表第 $\color{black}{k}$ 筆測試資料所需的最小成本。

## 範例輸入 #1

```
2
3 4
4 2 0 1
0 1 1 0
1 0 0 3
4 4
0 0 0 0
0 1 1 0
0 1 1 0
0 0 0 0
```

## 範例輸出 #1

```
1 2
2400
2 2
400
```
