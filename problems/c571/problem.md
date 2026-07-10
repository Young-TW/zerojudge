# c571. 三維偏序問題

## 內容

給出一個三維空間的點集$\color{black}{\space P \space}$(不保證點相異)，請問對於第$\color{black}{\space i \space}$個點，能從$\color{black}{\space P \space}$裡面找出多少點同時滿足$\color{black}{\space x_j > x_i, \space y_j > y_i \space 和 \space z_j > z_i \space}$?

## 輸入說明

第一行為一正整數$\color{black}{\space N \space (1 \leq N \leq 100000)}$，代表集合中的點數。


接下來的$\color{black}{\space N \space}$行分別有三個正整數$\color{black}{\space x_i, y_i, z_i \space (1 \leq x_i, \space y_i, \space z_i \leq N)}$，表示第$\color{black}{\space i \space}$個點的座標。

## 輸出說明

對於第$\color{black}{\space i \space}$行，輸出第$\color{black}{\space i \space}$個點的答案。

## 範例輸入 #1

```
10
7 2 6
8 6 4
6 6 3
3 1 7
8 7 8
8 7 2
7 10 1
5 6 4
1 3 1
7 3 1
```

## 範例輸出 #1

```
1
0
1
1
0
0
0
1
5
3
```
