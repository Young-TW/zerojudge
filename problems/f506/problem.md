# f506. 11747 - Heavy Cycle Edges

## 內容

找出最小生成樹有很多種方法，以下是其中一種方法：
一開始所有邊都在集合內
之後在圖中尋找環，把環上權重最重的邊移出集合，直到集合內沒有環


Given an undirected graph with edge weights, a minimum spanning tree is a subset of edges of minimum total weight such that any two nodes are connected by some path containing only these edges.A popular algorithm for finding the minimum spanning tree T in a graph proceeds as follows:
• let T be initially empty
• consider the edges e1, . . . , em in increasing order of weight – add ei to T if the endpoints of ei are not connected by a path in T
An alternative algorithm is the following:
• let T be initially the set of all edges
• while there is some cycle C in T – remove edge e from T where e has the heaviest weight in C
Your task is to implement a function related to this algorithm. Given an undirected graph G with edge weights, your task is to output all edges that are the heaviest edge in some cycle of G.

## 輸入說明

每筆測資第一行有N、M(1 ≤ n ≤ 1000 and 0 ≤ m ≤ 25000)分別代表點數和邊數，如果N和M都等於0則結束
接下來M行有a,b,w(0<w<2^31)分別代表邊的起點和終點以及權重，你可以假設這是張無向圖、沒有重邊、沒有任兩個邊的權重相同


The first input of each case begins with integers n and m with 1 ≤ n ≤ 1000 and 0 ≤ m ≤ 25000 where n is the number of nodes and m is the number of edges in the graph. Following this are m lines containing three integers u, v, and w describing a weight w edge connecting nodes u and v where 0 ≤ u, v < n and 0 ≤ w < 2^31. Input is terminated with a line containing n = m = 0; this case should not be processed. You may assume no two edges have the same weight and no two nodes are directly connected by more than one edge.

## 輸出說明

從小到大輸出被移除的邊之權重
如果沒有邊被移除則輸出"forest"(不含雙引號)


Output for an input case consists of a single line containing the weights of all edges that are the heaviest edge in some cycle of the input graph. These weights should appear in increasing order and consecutive weights should be separated by a space. If there are no cycles in the graph then output the text ‘forest’ instead of numbers.

## 範例輸入 #1

```
3 3
0 1 1
1 2 2
2 0 3
4 5
0 1 1
1 2 2
2 3 3
3 1 4
0 2 0
3 1
0 1 1
0 0
```

## 範例輸出 #1

```
3
2 4
forest
```
