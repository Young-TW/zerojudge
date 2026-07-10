# c459. 2. 自戀數

## 內容

一個 $\color{black}{d}$ 位數整數 $\color{black}{N = n_1 n_2 n_3 \ldots n_d， n_i \in \{1, 2, 3, 4, 5, 6, 7, 8, 9, 0\}}$ 被稱為自戀數 (narcissistic number) 若 $\color{black}{N = n_1^d + n_2^d + n_3^d + \ldots + n_d^d}$。
例如 $\color{black}{3}$ 位數整數 $\color{black}{153}$ 是自戀數因為 $\color{black}{153 = 1 ^ 3 + 5 ^ 3 + 3 ^ 3}$ ，而 $\color{black}{4}$ 位數整數 $\color{black}{1321}$ 不是自戀數因為 $\color{black}{1^4 + 3 ^ 4 + 2 ^ 4 + 1 ^ 4 = 99}$ 非 $\color{black}{1321}$。
非十進位制數字也會有自戀數，例如 $\color{black}{3}$ 進位制數字 $\color{black}{(122)_3 = 17}$ 且 $\color{black}{1^3 + 2 ^ 3 + 2 ^ 3 = 17}$，或 $\color{black}{5}$ 進位制數字 $\color{black}{(3134)_5 = 419}$ 且 $\color{black}{3^4 + 1^4 + 3^4 + 4^4 = 419}$。
請寫一個程式判斷一整數是否為自戀數。

## 輸入說明

第一列有兩個非負整數 $\color{black}{b}$ 與 $\color{black}{N}$，代表 $\color{black}{N}$ 為 $\color{black}{b}$ 進位制整數。

## 輸出說明

若輸出之整數為自戀數，輸出 YES，若否則輸出 NO。

## 範例輸入 #1

```
輸入範例 1：
10 153

輸入範例 2：
10 1321

輸入範例 3：
3 122

輸入範例 4：
5 3134
```

## 範例輸出 #1

```
輸出範例 1：
YES

輸出範例 2：
NO

輸出範例 3：
YES

輸出範例 4：
YES
```
