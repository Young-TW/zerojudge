# b596. Less is better

## 內容

There are some nails on a board, and we try to put a rope to include all the nails. We assume that the area of a single nail is zero, so the position of the nails can be present as a coordinate on the board. Furthermore, we want to minimize the num- ber of nails to fix the shape of the rope. For Example, if the coordinates of nails are (0,0),(2,1),(0,2),(2,4),(0,7),(2,8), we only need 4 nails to fix the rope. They are (0,0),(2,1),(2,8),(0,7), although the rope has touch all the 6 nails.



![image](ShowImage?id=882)

## 輸入說明

Each set of input data starts with the number of nodes n, 1 <= n <= 1000, and the second line contain a series of diference coordinates x and y, -10000 <= x, y <= 10000 with integers. Input data will end with single 0.

## 輸出說明

For each set of data, output the number of convex hull.

## 範例輸入 #1

```
5
0 0 2 0 0 2 2 2 1 1
6
0 0 2 1 0 2 2 4 0 7 2 8
0
```

## 範例輸出 #1

```
4
4
```
