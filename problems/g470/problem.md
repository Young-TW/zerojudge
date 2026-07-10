# g470. 12869: Zeroes

## 內容

Factorial n is written as n! and n! = 1∗2∗3∗. . .∗(n−1)∗n. For example 2! = 1∗2 = 2, 3! = 1∗2∗3 = 6, 5! = 120, 10! = 3, 628, 800, etc. The function fzero(n) denotes the number of trailing zeroes in n! in decimal number system. For example fzero(2) = 0, fzero(5) = 1, fzero(10) = 2. Given the domain of the input parameter v of fzero(v) function, you will have to find out how many different values of fzero() are there within this range.

## 輸入說明

The input file contains at most 50001 lines of inputs. Each line contains two positive integers low and high $(0 < low \leq high \leq 9*10^{18})$. Input is terminated by a line containing two zeroes.

## 輸出說明

For each line of input produce one line of output. This line contains an integer D, which denotes how many different values the function fzero(v) can have if $(low \leq v \leq high)$. Note: Illustration for Sample input 1: as 1! = 1, 2! = 2, 3! = 6, 4! = 24, 5! = 120, 6! = 720, 7! = 5,040, 8! = 40,320, 9! = 362,880, 10! = 3,628,800, so fzero(1) = 0, fzero(2) = 0, fzero(3) = 0, fzero(4) = 0, fzero(5) = 1, fzero(6) = 1, fzero(7) = 1, fzero(8) = 1, fzero(9) = 1 and fzero(10) = 2. So in this range (1 to 10) there are three different values of fzero(v): 0, 1 and 2.

## 範例輸入 #1

```
1 10
1 3
0 0
```

## 範例輸出 #1

```
3
1
```
