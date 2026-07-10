# r770. Commemorative Dice

## 內容

Since the year 2000, an ICPC regional contest has been held every year in Korea. To commemorate the 21st regional contest this year, it is decided to make a dice. The commemorative dice is a regular cube with a positive number written on each of its sides like an ordinary dice; However, the six numbers are not necessarily to be 1, 2, 3, 4, 5, 6 but just their sum is 21.

The dice can be used in various ways. For example, two people can play a game as follows: Each of the two picks one out of the many dice and then rolls the dice. The winner is the one who tosses a bigger number. It is important which dice to choose in this game because once the dice are set, the probability of one winning against the other is determined. Suppose that KyungYong chooses the dice shown in the figure below left and TaeCheon chooses the dice shown in the figure below right. Then, KyungYong wins when and only when TaeCheon tosses number 1, so the probability that KyungYong wins is 2/3.

![image](ShowImage?id=4995)

Given the dice of the first and second players, write a program to calculate the probability of the first player winning.

## 輸入說明

Your program is to read from standard input. The input consists of two lines. The first line contains six positive integers that are written on the sides of the dice of the first player. Also, the second line contains six positive integers that are written on the sides of the dice of the second player. The six integers given in a line add up to 21 and are separated by a single space.

## 輸出說明

Your program is to write to standard output. Print exactly one line that contains an irreducible fraction representing the probability of the first player winning. A fraction should consist of a numerator displayed before a slash and a non-zero denominator displayed after the slash. There are no spaces either before or after the slash. Note that an irreducible fraction refers to a fraction in which the numerator and denominator are integers that have no other common divisors than 1.

## 範例輸入 #1

```
3 4 3 4 3 4
1 1 1 1 8 9
```

## 範例輸出 #1

```
2/3
```

## 範例輸入 #2

```
1 2 3 4 5 6
3 4 3 4 3 4
```

## 範例輸出 #2

```
5/12
```

## 範例輸入 #3

```
1 2 3 4 5 6
8 7 2 2 1 1
```

## 範例輸出 #3

```
1/2
```
