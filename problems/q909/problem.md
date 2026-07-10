# q909. 11202 - The Least Possible Effort

## 內容

The Knight’s tour is a classic chess problem which was studied (and probably solved) over 1000 years ago. The problem is, from an arbitrary starting position, move a Knight chess piece around a chessboard visiting all other squares on the board exactly once. A related problem is to find all starting positions that get us to a
solution. For instance, in the chessboard above you can get a solution starting at the position numbered with 1 as well as 26, 54 and 7 (due to symmetry). This problem is more interesting if the board is not necessarily a square. Given a grid of n rows and m columns representing a board, 6 ≤ n, m ≤ 10000, find the minimum number of starting positions you must examine, such that we can find all the solutions for the Knight’s tour.


For example, in the grid on the right, the cells with the same color represent one cell and its symmetric ones; so we can examine only one cell of each color.

![image](ShowImage?id=4675)

![image](ShowImage?id=4677)


騎士巡邏問題是一個經典的西洋棋問題，早在1000多年前就已經被研究（甚至可能已經被解出）。該問題的目標是：從棋盤上任意一個起始位置開始，讓西洋棋的騎士（Knight）依規則移動，恰好拜訪棋盤上的每一格一次且僅一次。 現在我們試著找出所有可以產生完整解的起始位置。 舉例來說，在上圖中的棋盤，從編號為 1、26、54 和 7 的格子開始，都可以得到一個有效解，因為它們互為對稱。而這個問題在棋盤不一定是正方形的情況下更有趣。

## 輸入說明

The first line of the input contains an integer, t, indicating the number of test cases. For each test case, there is a line with two numbers separated by blanks, 6 ≤ n, m ≤ 10000, that is, the size of the board (n rows and m columns).


首行為正整數t，代表接下來測資行數
每行給定兩個正整數n,m(6 ≤ n, m ≤ 10000)，分別代表棋盤為 n 行、m 列。

## 輸出說明

For each test case, the output should consist of one line showing the minimum number of starting positions needed to find all the solutions of the Knight’s tour.

輸出你需要檢查多少個起始位置，才能涵蓋所有「不對稱」的騎士巡邏解。

## 範例輸入 #1

```
3
6 9
15 10
7 13
```

## 範例輸出 #1

```
15
40
28
```
