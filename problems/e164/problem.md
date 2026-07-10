# e164. 近衛問題

## 內容

你玩過《薩爾達傳說 曠野之息》嗎？這是款遊戲時數 30 分鐘左右的小品動作遊戲，而我們今天要解的問題和這款遊戲有一些些關聯。


好啦，不玩諧音爛梗了。給定一個正整數 $\color{black}{n}$ 的 $\color{black}{d_1}$ 進位表示，請你轉成 $\color{black}{d_2}$ 進位表示。

## 輸入說明

$\color{black}{T}$


$\color{black}{d_{1, 1}}$ $\color{black}{d_{1, 2}}$


$\color{black}{s_1}$


$\color{black}{d_{2, 1}}$ $\color{black}{d_{2, 2}}$


$\color{black}{s_2}$


$\color{black}{\vdots}$


$\color{black}{d_{T, 1}}$ $\color{black}{d_{T, 2}}$


$\color{black}{s_T}$



- $\color{black}{1 \le T \leq 1200}$。
- 對於所有的 $\color{black}{i \in \{1, 2, \ldots, T\}}$，均有
- $\color{black}{2\le d_{i, 1}\le36}$。
- $\color{black}{2\le d_{i, 2}\le36}$。
- $\color{black}{s_i}$ 為正整數 $\color{black}{n_i}$ 不含 leading zeros 的 $\color{black}{d_{i, 1}}$ 進位表示，其中 $\color{black}{n_i < 10^{5\times10^5}}$，且 $\color{black}{10}$ 到 $\color{black}{35}$ 分別以小寫字母的 a 到 z 表示；若 $\color{black}{T > 5}$，則 $\color{black}{n_i < 10^{50}}$。


- 輸入的數皆為整數。

## 輸出說明

$\color{black}{t_1}$


$\color{black}{t_2}$


$\color{black}{\vdots}$


$\color{black}{t_T}$



- $\color{black}{t_i}$ 為正整數 $\color{black}{n_i}$ 不含 leading zeros 的 $\color{black}{d_{i, 2}}$ 進位表示，且 $\color{black}{10}$ 到 $\color{black}{35}$ 也應分別以小寫字母的 a 到 z 表示。

## 範例輸入 #1

```
2
36 35
d53dv7uooz4
2 33
100100011001111010010100111000010001111101010001001010101011111101000000011
```

## 範例輸出 #1

```
hellohyrule
breathofthewild
```
