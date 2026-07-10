# e457. 也是 Segment Tree 練習

## 內容

uva 12532 Interval Product


最多n = 10^5 個數字 X1 ... Xn，K個詢問{只有兩種格式} C I V 或 P I J


C i v 是將Xi 的值改為v， P i j 是問 Xi ~ Xj 連續乘積的符號 {正、負、或0}輸出 +-0


有多組測資，每組輸出一列，請參考範例


其它的就請參考原題目了

## 輸入說明

Each test case is described using several lines. The first line contains two integers N and K, indicating respectively the number of elements in the sequence and the number of rounds of the game (1 ≤ N, K ≤ 105 ). The second line contains N integers Xi that represent the initial values of the sequence (−100 ≤ Xi ≤ 100 for i = 1, 2, . . . , N). Each of the next K lines describes a command and starts with an uppercase letter that is either ‘C’ or ‘P’. If the letter is ‘C’, the line describes a change command, and the letter is followed by two integers I and V indicating that XI must receive the value V (1 ≤ I ≤ N and −100 ≤ V ≤ 100). If the letter is ‘P’, the line describes a product command, and the letter is followed by two integers I and J indicating that the product from XI to XJ , inclusive must be calculated (1 ≤ I ≤ J ≤ N). Within each test case there is at least one product command.

## 輸出說明

For each test case output a line with a string representing the result of all the product commands in the test case. The i-th character of the string represents the result of the i-th product command. If the result of the command is positive the character must be ‘+’ (plus); if the result is negative the character must be ‘-’ (minus); if the result is zero the character must be ‘0’ (zero).

## 範例輸入 #1

```
4 6
-2 6 0 -1
C 1 10
P 1 4
C 3 7
P 2 2
C 4 -5
P 1 4
5 9
1 5 -2 4 3
P 1 2
P 1 5
C 4 -5
P 1 5
P 4 5
C 3 0
P 1 5
C 4 -5
C 4 -5
```

## 範例輸出 #1

```
0+-
+-+-0
```
