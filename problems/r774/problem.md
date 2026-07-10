# r774. Game

## 內容

Zzzz was secretly playing Spider Solitaire. Sometimes he won, sometimes he lost. Feeling someone's gaze, he stopped playing and started coding. Believing he'd evaded suspicion, he resumed the game. Then, during his brief coding stint, he noticed a noticeable improvement in his gaming skills.

Now, Zzzz won't lose in any future games. However, since he can't delete his game records, he believes his poor performances from the past don't prove his current prowess.

The game record looks like this:

- Number of games: X
- Games won: Y (Z%)
- Z is Zzzz's winning percentage, with the decimal point removed. For example, if X=53 and Y=47, then Z=88.

Given X and Y, write a program to find the minimum number of times Zzzz must play the game before Z changes.

## 輸入說明

Each line contains integers X and Y.

0<=X, Y<=10^9

## 輸出說明

On the first line, print the minimum number of rounds Zzzz needs to play. If Z never changes, print -1.

## 範例輸入 #1

```
10 8
```

## 範例輸出 #1

```
1
```

## 範例輸入 #2

```
100 80
```

## 範例輸出 #2

```
6
```

## 範例輸入 #3

```
47 47
```

## 範例輸出 #3

```
-1
```

## 範例輸入 #4

```
99000 0
```

## 範例輸出 #4

```
1000
```
