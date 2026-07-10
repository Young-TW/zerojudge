# c117. 00439 - Knight Moves

## 內容

你的一個朋友正在做一個關於西洋棋中騎士旅行問題（Traveling Knight Problem）的研究，他希望你幫他解決一個問題：就是給你2個格子的位置X及Y，請你找出騎士從X走到Y最少需要走幾步。

## 輸入說明

每筆測試資料一列。每列有2個西洋棋的座標位置。每個位置座標是由一個英文字母（a-h，代表棋盤的第幾欄）及一個數字（1-8，代表棋盤的第幾列）組成。

## 輸出說明

對每一列輸入，請輸出 "To get from xx to yy takes n knight moves.".

## 範例輸入 #1

```
e2 e4
a1 b2
b2 c3
a1 h8
a1 h7
h8 a1
b1 c3
f6 f6
```

## 範例輸出 #1

```
To get from e2 to e4 takes 2 knight moves.
To get from a1 to b2 takes 4 knight moves.
To get from b2 to c3 takes 2 knight moves.
To get from a1 to h8 takes 6 knight moves.
To get from a1 to h7 takes 5 knight moves.
To get from h8 to a1 takes 6 knight moves.
To get from b1 to c3 takes 1 knight moves.
To get from f6 to f6 takes 0 knight moves.
```
