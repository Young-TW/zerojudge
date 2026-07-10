# d141. Linearity

## 內容

A set of points is said to be collinear if they all lie on a single straight line. Clearly any two points are collinear since two points determine a line, but what about three points? Given three two-dimensional points (x,y), your program should determine if they are collinear.

## 輸入說明

Input will consist of multiple cases with the first line giving the number of cases. Each case will be on a separate line. Each case consists of three distinct ordered pairs of integers. The integers will be separated by a comma, and each ordered pair will be separated by a space.

## 輸出說明

For each set of three points, display whether or not they are collinear using the format shown in the example. In this example, the first three points line along the same line, while the second three do not.

## 範例輸入 #1

```
2
1,2 2,3 -30,-29
1,1 2,1 3,4
```

## 範例輸出 #1

```
collinear
not collinear
```
