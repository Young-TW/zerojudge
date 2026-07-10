# f710. 11489 - Integer Game

## 內容

有兩個無聊的人在玩一個無聊的遊戲，遊戲規則如下：
一開始有一串數字，兩人輪流取一個位數的數字
如果把這個數字去掉後，剩下的位數和能被3整除，這個位數的數字才能取
如果不能取，就輸了
假設兩個人都很聰明，問先手勝還是後手勝


Two players, S and T, are playing a game where they make alternate moves. S plays first.
In this game, they start with an integer N. In each move, a player removes one digit from the integer and passes the resulting number to the other player. The game continues in this fashion until a player finds he/she has no digit to remove when that player is declared as the loser.
With this restriction, its obvious that if the number of digits in N is odd then S wins otherwise T wins. To make the game more interesting, we apply one additional constraint. A player can remove a particular digit if the sum of digits of the resulting number is a multiple of 3 or there are no digits left.
Suppose N = 1234. S has 4 possible moves. That is, he can remove 1, 2, 3, or 4. Of these, two of them are valid moves.
Removal of 4 results in 123 and the sum of digits = 1 + 2 + 3 = 6; 6 is a multiple of 3.
Removal of 1 results in 234 and the sum of digits = 2 + 3 + 4 = 9; 9 is a multiple of 3.
The other two moves are invalid.
If both players play perfectly, who wins?

## 輸入說明

第一行有個T(T < 60)代表有幾筆測資
接下來T行，每行有一個不超過1000位的數字


The first line of input is an integer T (T < 60) that determines the number of test cases. Each case isa line that contains a positive integer N. N has at most 1000 digits and does not contain any zeros.

## 輸出說明

每筆測資輸出前先輸出"Case K: "(不含雙引號，K為第幾筆)
如果先手勝輸出"S"(不含雙引號)，否則輸出"T"(不含雙引號)


For each case, output the case number starting from 1. If S wins then output ‘S’ otherwise output ‘T’.

## 範例輸入 #1

```
3
4
33
771
```

## 範例輸出 #1

```
Case 1: S
Case 2: T
Case 3: T
```
