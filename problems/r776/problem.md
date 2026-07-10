# r776. Tree

## 內容

Tree T has a structure similar to Figure 1 below. Circles are called "vertices," and lines connecting them are called "edges." The topmost vertex is called the "root," and there is only one of them. The N vertices are numbered 1 through N, and the root is always 1.

A path connecting two vertices v and w is an ordered list of vertices (v 0 , v 1 , ..., v m ), where vertices v i and v i+1 are connected by an edge, such that v 0 = v, v m = w. In a tree, there is always exactly one path between any two vertices v and w . For example, in Figure 1, the unique path between vertices 3 and 11 is (3, 4, 1, 7, 11).

![image](ShowImage?id=4999)

For each vertex v, for a unique path P connecting the root r, among the vertices connected to the vertex v by an edge, the vertex on P is called the 'parent vertex' of v. For example, in Figure 1, the parent vertices of 4, 7, and 9 are 1, and the parent vertices of 2 and 11 are 7.

If you remove an edge connecting two vertices in a tree T, there may be other pairs of vertices for which no path exists. You need to answer a question like, "Is there a path connecting vertices v and w?" For example, if you remove the edge between 7 and 11 in Figure 1, there is no path connecting 8 and 5. 

Given tree information, edge removal information, and queries in any order, write a program that performs tasks in order and outputs answers to queries.

## 輸入說明

The following information is given as standard input. The first line contains two integers N and Q (1 ≤ N, Q ≤ 200,000), which represent the number of vertices in the tree and the number of queries. The ith line of the next N-1 lines contains an integer a representing the parent vertex of vertex i+1 (1 ≤ a ≤ N). Of the next (N-1)+Q lines, N-1 lines are given in the form of (1), and Q lines are given in the form of (2). (1) Two integers x and b are given (x = 0, 2 ≤ b ≤ N). This means that the edge connecting the parent vertex of b and b is removed. Each line contains a different value of b. (2) Three integers x, c, and d are given (x = 1, 1 ≤ c, d ≤ N). This means that the query is to find out whether there is a path connecting c and d.

## 輸出說明

Print the answers to the query in order on Q lines to standard output. For each line, print if the path exists YES, otherwise NOprint .

## 範例輸入 #1

```
3 3
1
1
1 2 3
0 3
1 2 3
1 1 2
0 2
```

## 範例輸出 #1

```
YES
NO
YES
```

## 範例輸入 #2

```
11 5
7
4
1
9
11
1
11
1
3
7
0 11
1 8 5
1 3 9
0 10
0 9
0 7
1 2 7
0 5
1 1 10
0 8
0 6
0 2
1 1 3
0 3
0 4
```

## 範例輸出 #2

```
NO
YES
YES
NO
YES
```
