# a073. POJ2832 How Many Pairs?

## 內容

You are given an undirected graph G with N vertices and M edges. Each edge has a length. Below are two definitions.

- Define max_len(p) as the length of the edge with the maximum length of p where p is an arbitrary non-empty path in G. 
- Define min_pair(u, v) as min{max_len(p) | p is a path connecting the vertices u and v.}. If there is no paths connecting u and v, min_pair(u, v) is defined as infinity.
Your task is to count the number of (unordered) pairs of vertices u and v satisfying the condition that min_pair(u, v) is not greater than a given integer A.

## 輸入說明

The first line of input contains three integer N, M and Q (1 < N ≤ 100,000, 0 < M ≤ 200,000, 0 < Q ≤ 200,000). N is the number of vertices, M is the number of edges and Q is the number of queries. Each of the next M lines contains three integers a, b, and c (1 ≤ a, b ≤ N, 0 ≤ c < 108) describing an edge connecting the vertices a and b with length c. Each of the following Q lines gives a query consisting of a single integer A (0 ≤ A < 108).

## 輸出說明

Output the answer to each query on a separate line.

## 範例輸入 #1

```
4 5 4
1 2 1
2 3 2
2 3 5
3 4 3
4 1 4
0
1
3
2
```

## 範例輸出 #1

```
0
1
6
3
```
