# f989. 線上焼鳮學習

## 內容

焼鳮有很多維度，所以你找了一個 $\color{black}{n}\ $ 維的烤架。


這個烤架格子的座標範圍從 $\color{black}{(1,\ 1,...,\ 1,\ 1)}\ $ 到 $\color{black}{(m_1,\ m_2,...,\ m_{n-1},\ m_n)}\ $，初始的狀態都是熄滅的。


你可以對這個 $\color{black}{n}\ $ 維烤架做以下兩種操作：


- $\color{black}{1}\ $：將座標為 $\color{black}{(x_1,\ x_2,...,\ x_{n-1},\ x_n)}\ $ 的格子狀態改變，也就是從熄滅的變點燃的，或是從點燃的變熄滅的。
- $\color{black}{2}\ $：計算範圍 $\color{black}{(l_1,\ l_2,...,\ l_{n-1},\ l_n)}\ $ 到 $\color{black}{(r_1,\ r_2,...,\ r_{n-1},\ r_n)}\ $ 總共有多少格子是點燃的。

## 輸入說明

第一行有 $\color{black}{t}\ $，代表測資筆數。


每筆測資第一行有 $\color{black}{n,\ q}\ $，代表這個烤架是幾維的和總共有幾筆操作。


第二行有 $\color{black}{m_1\sim m_n}\ $，代表烤架每維寬度。


接下來 $\color{black}{q}\ $ 行，每行開頭若為 $\color{black}{1}\ $，則接著輸入 $\color{black}{x_1\sim x_n}\ $，並進行操作 $\color{black}{1}\ $；開頭若為 $\color{black}{2}\ $，則接著先輸入 $\color{black}{l_1\sim l_n}\ $，再輸入 $\color{black}{r_1\sim r_n}\ $，並進行操作 $\color{black}{2}\ $。


- $\color{black}{1≤t≤10}\ $
- $\color{black}{1≤n≤8,\ 1≤q≤10^4}\ $
- $\color{black}{1≤m_i≤10^5,\ \prod\limits_{i=1}^{n}m_i≤10^5}\ $
- $\color{black}{1≤x_i≤m_i,\ 1≤l_i≤r_i≤m_i}\ $

## 輸出說明

對於每個操作 $\color{black}{2}\ $，輸出答案。

## 範例輸入 #1

```
2

3 10
2 2 2
1 1 1 1
1 1 2 1
2 1 1 1 2 2 2
2 1 1 1 2 1 2
1 1 1 2
1 1 1 1
2 1 1 1 2 2 2
2 1 1 2 2 2 2
1 1 1 1
2 1 1 1 2 2 2

1 5
100
1 74
1 47
2 55 100
2 7 47
2 1 100
```

## 範例輸出 #1

```
2
1
2
1
3
1
1
2
```
