# r802. B. The Phase-Swapped Labyrinth

## 內容

This labyrinth exists in two overlapping phases.
Each cell may be open or blocked depending on the current phase.

You start in phase 0.
Some cells force an instant phase switch when entered.

Your goal is to reach the exit in the minimum number of steps.

## 輸入說明

A grid of characters describing walls, open paths, and phase-switch tiles.

- 1 ≤ n, m ≤ 200

## 輸出說明

Output the minimum number of steps needed to reach the exit, or -1.

## 範例輸入 #1

```
3 4
..S.
##.#
..#.
```

## 範例輸出 #1

```
-1
```
