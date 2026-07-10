# b599. Graph Construction

## 內容

A graph is a collection of edges E and vertices V . There are many different ways to represent a graph in a computer. Graphs can be represented by adjacency matrix or by adjacency list. There are some other ways to represent graph. One of them is to write the degrees (the numbers of edges that a vertex has) of each vertex. If there are n vertices then n integers can represent the graph. In this problem, we are talking about simple graph which does not have same pairs of endpoints for more than one edge, and also does not have edges with the same endpoint.


An example is shown as follows. The graph can be represented as 1, 3, 2 and 2.



![image](ShowImage?id=883)
Any graph can be represented by n number of integers. But the reverse is not always true. If you are given n integers, you have to find out whether these n numbers can represent the degrees of n vertices of a graph.

## 輸入說明

The input contains several test cases. Each test case consists of two lines. Each test case starts a line with an integer n, 1 <= n <= 1000, where n is the number of vertices in the graph. The following line contains n numbers which represents the degrees of n vertices of the graph. Input is terminated with a single zero.

## 輸出說明

If the n integers can represent a graph then output 'Y'. Otherwise output 'N'. Output for each test case should be in a separate line.

## 範例輸入 #1

```
4
3 3 3 3
6
2 4 5 5 2 1
5
3 2 3 2 1
0
```

## 範例輸出 #1

```
Y
N
N
```
