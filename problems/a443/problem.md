# a443. 10720 - Graph Construction

## 內容

Graph is a collection of edges E and vertices V. Graph has a wide variety of applications in computer. There are different ways to represent graph in computer. It can be represented by adjacency matrix or by adjacency list. There are some other ways to represent graph. One of them is to write the degrees (the numbers of edges that a vertex has) of each vertex. If there aren vertices then n integers can represent that graph. In this problem we are talking about simple graph which does not have same endpoints for more than one edge, and also does not have edges with the same endpoint.

Any graph can be represented by n number of integers. But the reverse is not always true. If you are given n integers, you have to find out whether thisn numbers can represent the degrees of n vertices of a graph.

輸入一張圖的度序列，問有沒有可能是一張簡單圖的度序列

※簡單圖:無自環(loop)、無重邊

## 輸入說明

Each line will start with the number n (≤ 1000000). The next n integers will represent the degrees of n vertices of the graph. A 0 input for n will indicate end of input which should not be processed.
※注意N的範圍與原題不同

## 輸出說明

If the n integers can represent a graph then print “Possible”.  Otherwise print “Not possible”. Output for each test case should be on  separate line.

## 範例輸入 #1

```
4 3 3 3 3
6 2 4 5 5 2 1
5 3 2 3 2 1
0
```

## 範例輸出 #1

```
Possible
Not possible
Not possible
```
