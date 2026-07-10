# b478. 有限間距最長共同子序列

## 內容

背景 有限間距最長共同子序列 (Gapped Longest Common Subsequence, 簡稱 GLCS) 是一種 LCS 的變形，而 LCS 想必早已成了經典題型。

回顧一下最長共同子序列 LCS 的解法，可以利用最簡單的 $O(NM)$ 動態規劃完成或者在特殊不重複情況下轉化成 LIS 在 $O(N \log N)$ 時間完成，轉換成 LIS 是有風險的，有機會退化成 $O(NM \log N)$。說不定還有比 $O(NM)$ 更快的算法去計算 LCS。

GLCS 的特點在於挑選子序列時，挑選到的相鄰字符位置之間最多有 $K$ 個字符不選。可強迫挑選出的相似序列盡可能是有意義的。

例如兩個字符串 $S, \; T$ 要求 GLCS，當 $K = 2$ 時：

$$S = \text{ACBDCAA} \\ T = \text{ADDBCDBAC} $$

則 `ABCA` 是一組合法的 $K = 2$  時的 GLCS，挑選方案如下

```
    0123456789
S = ACBDCAA
    ^ ^ ^^
T = ADDBCDBAC
    ^  ^^  ^
```
若 $K = 1$ 時，由於字符串 $T$ 挑選 `ABCA` 時，前兩個字符之間的不選字符數為 2，不符合小於等於 $K$，則 `ABCA` 不能是 $K = 1$ 的合法 GLCS，而 `CDA` 是一組合法 $K = 1$ 時的 GLCS。

```
    0123456789
S = ACBDCAA
     ^ ^ ^
T = ADDBCDBAC
        ^^ ^
```
題目描述給予兩個字符串 $S, \; T$ 以及限制間距 $K$，求出 GLCS 的長度為何。

## 輸入說明

有多組測資。

每組測資一行為 $K, \; S, \; T$，其中 $S, \; T$ 只由大寫字母組成。

- $ 0\le K \le 2000$
- $0 < len(S), len(T) \le 2000$

## 輸出說明

對於每一組測資，輸出一行一個整數，表示 GLCS 的長度。

## 範例輸入 #1

```
2 ACBDCAA ADDBCDBAC
1 ACBDCAA ADDBCDBAC
0 ACBDCAA ADDBCDBAC
```

## 範例輸出 #1

```
4
3
2
```
