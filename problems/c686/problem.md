# c686. 高斯符號

## 內容

高斯符號 $\color{black}{[x]}$，代表不超過$\color{black}{x}$的最大整數，例如 $\color{black}{[\pi] = 3, [-1.5] = -2}$。


有時候會看到 $\color{black}{\lceil x \rceil 或 \lfloor x \rfloor (同 [x])}$ ，則分別代表向上和向下取整。


現在給兩個正整數 $\color{black}{n, m}$，請求出 $\color{black}{\displaystyle\sum_{k=1}^{n}\left[\frac{km}{n}\right]}\space$的值。

## 輸入說明

每行有兩個正整數 $\color{black}{n, m \le 10^9}$。

## 輸出說明

輸出答案。

## 範例輸入 #1

```
53 97
1 100
```

## 範例輸出 #1

```
2593
100
```
