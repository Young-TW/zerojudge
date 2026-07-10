# b431. 中國餘數

## 內容

背景中國餘數定理 (Chinese Remainder Theorem，簡稱 CRT) 經常是工程學裡面常用的一種轉換域，很多人不知道當初在大學離散數學中學這個做什麼，但是在不少計算的設計都會運用到 CRT。由於電腦 CPU 架構中的運算單位是 32-bits 或者 64-bits (也許在未來會更長)，但值域高達 128-bits 或者 512-bits 以上模擬運算成了麻煩之處。

回顧中國餘數定理 CRT

$$ (S): \left\{\begin{matrix}
x \equiv a_1 \mod m_1 \\
x \equiv a_2 \mod m_2 \\
\vdots \\
x \equiv a_n \mod m_n
\end{matrix}\right. $$

- $ m_1, m_2, \cdots , m_n $ 任兩數互質，意即 $ \forall i \neq j, gcd(m_i, m_j) = 1$
- 對於任意整數 $ a_1, a_2, \cdots , a_n $ 方程組 $(S)$ 均有解，意即找得到一個 $x$ 的參數解。
構造法解 CRT

- 設 $M = m_1 \times m_2 \times \cdots \times m_n = \prod_{i=1}^{n} m_i$
- 設 $M_i = M / m_i$
- 設 $t_i = M_i^{-1} \mod m_i$，意即 $t_i M_i \equiv 1 \mod m_i$
- 方程組 $(S)$ 的通解形式為：
$$x = a_1 t_1 M_1 + a_2 t_2 M_2 + \cdots + a_n t_n M_n + kM = kM + \sum_{i = 1}^{n} a_i t_i M_i, k \in \mathbb{Z}$$
- 若限定 $0 \le x < M$，則 $x$ 只有一解。
很多人會納悶通解為什麼長那樣，原因很簡單，要滿足方程組每一條式子，勢必對於 $a_i t_i M_i$ 要滿足 $x \equiv a_i \mod m_i$ ，因此  $a_i t_i M_i \equiv a_i (t_i M_i) \mod m_i \equiv a_i \mod m_i$ 成立，但是 $ \forall i \neq j$，滿足 $a_i t_i M_i \equiv a_i (t_i M_i) \mod m_j \equiv 0 \mod m_j$

問題描述來個簡單運用，來計算簡單的 RSA 加解密，特化其中的數學運算。

$$M \equiv C^d \mod n$$

$n = p \times q$，其中 $p, q$ 是兩個不同的質數，已知 $C, d, p, q$，請求出 $M$。

## 輸入說明

有多組測資，每一組測資一行四個整數 $C, d, p, q$，其中 $ 2 \le p, q \le 10^9$, $ 0 \le C \le p \times q, 0 \le d \le (p-1)(q-1) $。保證 $p, q$ 是兩個不同的質數。

## 輸出說明

對於每一組測資輸出一行，$M \equiv C^d \mod n$ 的結果。

## 範例輸入 #1

```
88 7 17 11
11 23 17 11
```

## 範例輸出 #1

```
11
88
```
