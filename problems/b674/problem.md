# b674. Is It A Tree

## 內容

A tree is a well-known data structure that is either empty or is a set of one or more nodes connected by directed edges between nodes satisfying the following properties.


- There is exactly one node, called the root, to which no directed edges point.
- Every node except the root has exactly one edge pointing to it.
- There is a unique sequence of directed edges from the root to each node.

For example, consider the graphs given below, in which circles represent nodes and lines with arrowheads represent edges. The first two of these are trees, but the last is not.


 
![image](ShowImage?id=888)


In this problem you will be given several descriptions of collections of nodes connected by directed edges. For each of these you are to determine if the collection satisfies the definition of a tree or not.

## 輸入說明

Each test case contains two lines. The first line is the number of edges n, 1 <= n <= 1000, and the second line consists of a sequence of edges. Each edge consists of a pair of integers u and v, 1 <= u, v <= 1000. The first integer u identifies the node from which the edge begins, and the second integer v identifies the node to which the edge is directed. It is easy to see that this line must contain even number of integers. A line with 0 signifies the end of input.

## 輸出說明

Output 'y' if the test case is a tree; otherwise output 'n'.

## 範例輸入 #1

```
5
6 8 5 3 5 2 6 4 5 6
8
8 1 7 3 6 2 8 9 7 5 7 4 7 8 7 6
6
3 8 6 8 6 4 5 3 5 6 5 2
0
```

## 範例輸出 #1

```
y
y
n
```
