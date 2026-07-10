# a563. ITSA201210 P2 Median of a tree

## 內容

For two nodes in a graph, the distance between them is the minimum number of
edges in any path connecting the two nodes. The median of a graph is the node with
minimum total distance to all the others. A tree is a graph in which, for any two nodes,
there is a unique path. In this problem, your task is to write a program to compute the
median of a tree. If there is more than one median, output the one with smaller label.
Note that simply computing the total distances will take too much time.

## 輸入說明

The input is a rooted tree. The first line is an integer n, 1 < n ≦ 90000, which is
the number of nodes. The nodes are given by their unique labels which are integers
from 0 to n-1, and the root is node 0. In the second line, there are n-1 integers which
are the parents of nodes 1, 2,…, n-1, respectively. For any node i, the label of its
parent is smaller than its label.

## 輸出說明

Output the median in one line. If there is more than one median, output the one
with smaller label.

## 範例輸入 #1

```
5
0 1 1 3
```

## 範例輸出 #1

```
1
```
