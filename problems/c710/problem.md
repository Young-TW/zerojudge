# c710. 分玩具

## 內容

在 $\color{black}{A?}$ 家中，有許多倉庫排成一列，每個倉庫都堆放著一種玩具。


今天 $\color{black}{A?}$ 決定送出一些玩具給鎮上的小孩。他打算將編號 $\color{black}{l}$ 和 $\color{black}{r}$ 之間倉庫的玩具都搬上貨車，卻隨即發現有些玩具無法平分。
於是他列出 $\color{black}{M}$ 個送禮計畫，請你幫忙計算每個計畫能送出多少種玩具。

## 輸入說明

第一行為兩正整數 $\color{black}{N, \space M \space (1 \le N, \space M \le 300000)}$ 分別代表倉庫和計畫的數量。


第二行為各個倉庫所堆放的玩具數量 $\color{black}{C_1, C_2, \cdots, C_i, \cdots, C_N \space (1 \le C_i \le N)}$。


接下來 $\color{black}{M}$ 行分別有三個正整數 $\color{black}{l, \space r, \space k \space (1 \le l \le r \le N, \space 1 \le k \le N)}$ 代表 $\color{black}{A?}$ 要送出 $\color{black}{l}$ 號倉庫到 $\color{black}{r}$ 號倉庫的禮物給 $\color{black}{k}$ 個孩子。

## 輸出說明

依序輸出每個送禮計畫中有多少種玩具能被送出。

## 範例輸入 #1

```
5 3
1 2 3 2 2
1 5 1
1 5 2
1 5 3
```

## 範例輸出 #1

```
5
3
1
```
