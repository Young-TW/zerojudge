# b604. Center of Symmetry

## 內容

Given a set of n points in a plane with integer coordinates (xi, yi), i = 1, 2, . . . , n. Your task is to decide whether the set of points has a center of symmetry or not.


A set of points S has a center of symmetry if there exists a point s (not necessarily in S) such that for every point p in S there exists a point q in S such that p - s = s - q.

## 輸入說明

For each case, the first line contains a number n, 1 <= n <= 10000. The subsequent n 


lines contain two integers, which are the x and y coordinates of the point. Every point is unique and -10000000 <= x, y <= 10000000. A line with 0 (n = 0) signifies the end of input. A figure shown below is the sample input.



![image](ShowImage?id=886)

## 輸出說明

For each set of input data print "yes" if the set of points has a center of symmetry and "no" otherwise.

## 範例輸入 #1

```
8
1 10
3 6
6 8
6 2
3 -4
1 0
-2 -2
-2 4
0
```

## 範例輸出 #1

```
yes
```
