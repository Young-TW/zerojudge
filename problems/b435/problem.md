# b435. 尋找原根

## 內容

原根(primitive root)是在數論中一個很重要的概念。

模$m$的原根(A primitive root modulo $m$)是一個正整數$g$，使得
\[g^{\phi(m)} \equiv 1 (\mathrm{mod}~m)\]
且
\[g^\gamma \not \equiv 1 (\mathrm{mod}~m)\]
對$1 \leq \gamma < \phi(m)$恒成立。

其中$\phi(m)$是歐拉(Euler)函數。

對於一個模$m$的原根$g$， 他的冪$g^0,g^1,\dots,g^{\phi(m)-1}$組成了模$m$的簡化剩餘系(a reduced system of residues modulo $m$)。

現在你的任務就是，給你一個質數模$p$，求出$p$的最小原根。

## 輸入說明

有若干筆測資。每筆測資占一行，只有一個質數$p(2 \leq p \leq 2,100,000,000)$。

## 輸出說明

對每筆測資，輸出一個數字并換行，表示對應的$p$的最小原根。

## 範例輸入 #1

```
2
3
5
7
```

## 範例輸出 #1

```
1
2
2
3
```
