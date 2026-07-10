# a962. 新專輯

## 內容

給定正整數 $\color{black}{N}$，請求出 $\color{black}{\left(N\operatorname{mod}1+N\operatorname{mod}2+\ldots+N\operatorname{mod}N\right)}$ 除以 $\color{black}{10^9+9}$ 的餘數。這裡 $\color{black}{a\operatorname{mod}m}$ 定義為 $\color{black}{a}$ 除以 $\color{black}{m}$ 的餘數，即唯一的非負整數 $\color{black}{r}$ 滿足 $\color{black}{r<|m|}$ 且 $\color{black}{a-r}$ 能被 $\color{black}{m}$ 整除。

## 輸入說明

$\color{black}{N}$
- $\color{black}{1\le N\le10^{14}}$。
- $\color{black}{N}$ 為整數。

## 輸出說明

$\color{black}{S}$
- $\color{black}{S}$ 為一整數，代表 $\color{black}{\left(N\operatorname{mod}1+N\operatorname{mod}2+\ldots+N\operatorname{mod}N\right)}$ 除以 $\color{black}{10^9+9}$ 的餘數。

## 範例輸入 #1

```
10
```

## 範例輸出 #1

```
13
```

## 範例輸入 #2

```
50
```

## 範例輸出 #2

```
420
```

## 範例輸入 #3

```
100000000000000
```

## 範例輸出 #3

```
45752744
```
