# r801. A. The Time-Locked Sanctuary

## 內容

The sanctuary floor is an N × M grid where each tile is sealed by a time lock.
Each tile contains a number representing the earliest time it can be entered.

You start at the top-left corner at time 0.
You may move in four directions, each move taking exactly one unit of time,
and you may wait in place for any amount of time.

You must reach the bottom-right corner as early as possible.

## 輸入說明

One grid where each cell gives the earliest time you are allowed to step on that cell.

- 
1 ≤ n, m ≤ 300

- 
0 ≤ aij ≤ 10^9

## 輸出說明

Output the minimum time to reach the destination, or -1 if it is impossible.

## 範例輸入 #1

```
3 3
0 2 4
1 3 5
2 4 6
```

## 範例輸出 #1

```
6
```
