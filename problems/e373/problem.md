# e373. 一元二次同餘方程式

## 內容

給定質數 $\color{black}{p}$ 與三個非負整數 $\color{black}{a, b, c}$，其中 $\color{black}{0 \leq a, b, c \leq p-1}$ 且 $\color{black}{a \neq 0}$，請找出同餘方程式 $\color{black}{ax^2+bx+c \equiv 0\ (\operatorname{mod}p)}$ 在 $\color{black}{\{0, 1, \ldots, p-1\}}$ 內的根。

## 輸入說明

本題的輸入檔有多筆測試資料，請讀至檔案尾。
每筆測試資料佔一行，包含以一空白隔開的四個非負整數 $\color{black}{p, a, b, c}$。


- 測試資料總數不超過 $\color{black}{10^5}$。
- $\color{black}{p}$ 為質數且 $\color{black}{2 \leq p < 2^{31}}$。
- $\color{black}{0 \leq a, b, c \leq p-1}$ 且 $\color{black}{a \neq 0}$。

## 輸出說明

對於每筆測試資料，輸出一行，包含方程式 $\color{black}{ax^2+bx+c \equiv 0\ (\operatorname{mod}p)}$ 在 $\color{black}{\{0, 1, \ldots, p-1\}}$ 內的根。如果有多個根，請以一空白隔開由小到大輸出。如果不存在這樣的 $\color{black}{x}$，請輸出 "no solution" (不含引號)。

## 範例輸入 #1

```
2 1 1 0
3 2 1 2
5 4 3 2
2147483647 123456789 999999999 987654321
```

## 範例輸出 #1

```
0 1
2
no solution
516628045 1897947583
```
