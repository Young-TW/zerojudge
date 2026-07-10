# a605. 交錯和

## 內容

給定一個整數數列 $\color{black}{\mathbf{a} = a_1, a_2, \ldots, a_n}$。對於每個下標數列 $\color{black}{\mathbf{i} = i_1, i_2, \ldots, i_m}$，其中 $\color{black}{m\ne0}$ 且 $\color{black}{1\le i_1<i_2<\ldots<i_m\le n}$，我們定義交錯和 $\color{black}{\sigma(\mathbf{i}; \mathbf{a})}$ 為 $\color{black}{a_{i_1} - a_{i_2} + a_{i_3} - a_{i_4} + \ldots + (-1)^{m-1}a_{i_m}}$。

 

已知對於所有 $\color{black}{1}$ 到 $\color{black}{m-1}$ 之間的整數 $\color{black}{j}$，均有 $\color{black}{i_{j+1}-i_j \le \delta}$，請求出 $\color{black}{\sigma(\mathbf{i}; \mathbf{a})}$ 的最大值。

## 輸入說明

$\color{black}{n}$ $\color{black}{\delta}$


$\color{black}{a_1}$ $\color{black}{a_2}$ $\color{black}{\ldots}$ $\color{black}{a_n}$



- $\color{black}{1 \le n \le 10^6}$。
- $\color{black}{1 \le \delta \le n}$。
- 對於所有的 $\color{black}{k \in \{1, 2, \ldots, n\}}$，均有 $\color{black}{-2^{31} \le a_k \le 2^{31}-1}$。
- 輸入的數皆為整數。

## 輸出說明

$\color{black}{S}$
- $\color{black}{S}$ 為一整數，代表在滿足 $\color{black}{i_{j+1}-i_j \le \delta}$ 的限制下，$\color{black}{\sigma(\mathbf{i}; \mathbf{a})}$ 的最大值。

## 範例輸入 #1

```
5 1
1 4 3 2 5
```

## 範例輸出 #1

```
6
```

## 範例輸入 #2

```
5 2
1 4 3 2 5
```

## 範例輸出 #2

```
7
```

## 範例輸入 #3

```
10 4
-10 -9 -8 -7 -6 -5 -4 -3 -2 -1
```

## 範例輸出 #3

```
-1
```
