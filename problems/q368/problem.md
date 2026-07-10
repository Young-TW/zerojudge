# q368. 3. 阿克曼函數

## 內容

德國數學家 Wilhelm Ackermann 在 1928 年的一篇論文 "Zum Hilbertschen Aufbau der reellen Zahlen"中，提出了一個三變數遞迴函數：


$$
\phi(m, n, p)=
\begin{cases}
n+p, &\text{if }m=0\\
n, &\text{if }m=1\\
1, &\text{if }m=2\ \wedge\ p=0\\
0, &\text{if }m\ge3\ \wedge\ p=0\\
\phi(m-1, n, \phi(m, n, p-1)), &\text{otherwise}
\end{cases}
$$


這個函數是用來研究可計算函數與形式系統的自洽性，是數理邏輯領域的一部分，並且當時被用來研究原始遞迴函數的極限。
　　匈牙利數學家 Rózsa Péter 在 1935 年的成果使得阿克曼函數成為研究「可計算性」的重要範例，特別是在比較「原始遞迴函數」與「一般遞迴函數」的時候，阿克曼函數成為經典案例。
　　1947 年，美國數學家 Raphael M.Robinson 將 Péter 的研究進一步推廣，成為我們現在熟知的形式：


$$
\text A(m, n)=
\begin{cases}
n+1, &\text{if }m=0\\
\text A(m-1, 1), &\text{if }m>0\ \wedge\ n=0\\
\text A(m-1, \text A(m, n-1)), &\text{if }m>0\ \wedge\ n>0\\
\end{cases}
$$


這個版本目前被廣泛應用於計算理論和計算機科學。

## 輸入說明

輸入包含兩個正整數 $m, n$（$0\le m\le 3$, $0\le n\le 11$）。

## 輸出說明

請輸出 $\text A(m, n)$ 於一行。

## 範例輸入 #1

```
1 2
```

## 範例輸出 #1

```
4
```

## 範例輸入 #2

```
3 11
```

## 範例輸出 #2

```
16381
```
