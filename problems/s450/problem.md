# s450. Problem A: Cosmic Barrier

## 內容

A team of space archaeologists has discovered a cluster of $N$ ancient energy monoliths on a two-dimensional planetary plane. The position of the $i$-th monolith is given by integer coordinates $(x_i, y_i)$. To conduct research safely without triggering an energy chain reaction, they need to deploy a straight-line laser barrier $L$.
Due to the unstable gravitational fluctuations at the coordinate origin $(0,0)$, the barrier $L$ cannot be placed too close to the center. Specifically, the perpendicular distance from the origin $(0,0)$ to the line $L$ must be at least $R$.
The hazard level of the barrier setup is defined as the maximum perpendicular distance from any of the $N$ monoliths to the line $L$. The archaeologists want to find a valid line $L$ that minimizes this hazard level. Can you help them compute the minimum possible hazard level?

## 輸入說明

The first line contains two integers $N$ and $R$ ($3 \le N \le 10^5$, $0 \le R \le 10^6$) — the number of monoliths and the minimum allowed distance from the origin to the barrier.
Each of the next $N$ lines contains two integers $x_i$ and $y_i$ ($-10^6 \le x_i, y_i \le 10^6$) — the coordinates of the $i$-th monolith.
It is guaranteed that the monoliths are not all collinear, and no monolith is located exactly at the origin.

## 輸出說明

Output a single floating-point number representing the minimum possible hazard level. Your answer will be accepted if its absolute or relative error does not exceed $10^{-9}$.

## 範例輸入 #1

```
4 0
2 2
-2 2
-2 -2
2 -2
```

## 範例輸出 #1

```
2.0000000000
```

## 範例輸入 #2

```
4 3
2 2
-2 2
-2 -2
2 -2
```

## 範例輸出 #2

```
5.0000000000
```
