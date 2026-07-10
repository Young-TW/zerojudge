# c661. Zer0

## 內容

$\color{black}{1! = 1}$
$\color{black}{2! = 2}$
$\color{black}{10! = 3628800}$
$\color{black}{\cdots}$


計算 $\color{black}{n!}$ 結尾有多少個零對你來說早已不是難題（如 d122），現在我們關注較為複雜的狀況：


$\color{black}{\displaystyle\prod_{k=n}^{m}k!}\space$的答案為何？


也就是說，你必須算出$\color{black}{n! * (n+1)! * (n+2)! * \cdots * (m-1)! * m!}\space$結尾零的個數。

## 輸入說明

第一行有一個正整數$\space\color{black}{T <= 100000}$，代表測資筆數。


接下來的$\space\color{black}{T}\space$行，每行有兩個整數$\color{black}{1 <= n <= m <= 10^9}$。

## 輸出說明

輸出$\color{black}{\displaystyle\prod_{k=n}^{m}k!}\space$結尾零的個數。

## 範例輸入 #1

```
2
1 1
1 10
```

## 範例輸出 #1

```
0
7
```
