# g471. 12959: Strategy Game

## 內容

A strategy game with $J$ players is played around a table. Players are identified by numbers from 1 to $J$ and will play a total of $R$ rounds. At each round each player will play once, in the order of their identifiers; that is, player 1 will play first, player 2 will play second, and so on. Once player $J$ plays, the round is complete, and a next round starts. A player earns a certain amount of Victory Points every time she or he plays. After all rounds are finished the total points of each player is computed as the sum of Victory Points the player earned on each round. The winner is the player with the maximum number of points; in case of a tie the winner is the player who earned the maximum number of points and played last. Given the number of players, the number of rounds and a list describing the Victory Points in the order they were obtained, you must determine which player is the winner.

## 輸入說明

The input contains several test cases. In each test case, the first line contains two integers $J$ and $R$, respectively the number of players and the number of turns $(1 \leq J, R \leq 500)$. The second line contains $J \cdot R$ integers, representing the Victory Points earned by each player in each turn, in the order they happened. The Victory Points obtained in each turn will be always integer numbers between $0$ and $100$, inclusive. If both $J$ and $R$ are of values zero, then the input ends.

## 輸出說明

For each test case in the input, your program must produce one single line, containing the integer representing the winner.

## 範例輸入 #1

```
3 3
1 1 1 1 2 2 2 3 3
2 3
0 0 1 0 2 0
0 0
```

## 範例輸出 #1

```
3
1
```
