# c425. 字典序第K小旋轉

## 內容

這次就不編故事了，直接來吧！


設$s = s_1s_2\ldots s_n$為任意字串。我們將「把$s_1$挪到字串尾端」的操作稱為左旋轉，記作$\mathcal{L}$，亦即$\mathcal{L}s = s_2s_3\ldots s_ns_1$。注意對於每個$0 \leq k \leq n-1$，我們有$\mathcal{L}^ks = s_{k+1}s_{k+2}\ldots s_ns_1s_2 \ldots s_k$，稱為$s$的一個旋轉。


現在給定一個全由小寫英文字母組成的字串$s[1 \ldots n]$以及一個不超過$n$正整數$K$，請求出在$s, \mathcal{L}s, \mathcal{L}^2s, \ldots, \mathcal{L}^{n-1}s$當中，字典序第$K$小的字串。

## 輸入說明

輸入的第一行有一個正整數$T$，代表接下來有幾筆測試資料


每筆測試資料佔一行，包含了一個全由小寫英文字母組成的字串$s$，以及不超過$|s|$的正整數$K$，以一個空白隔開。


- $T \leq 10$
- $|s| \leq 2\times 10^6$
- $1 \leq K \leq |s|$

## 輸出說明

對於每筆測試資料，輸出在$s, \mathcal{L}s, \mathcal{L}^2s, \ldots, \mathcal{L}^{n-1}s$當中，字典序第$K$小的字串，佔一行。

## 範例輸入 #1

```
2
aabac 3
prpr 2
```

## 範例輸出 #1

```
acaab
prpr
```
