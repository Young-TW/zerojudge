# r783. Tree cutting

## 內容

Sanggeun needs a meter of wood. Since all nearby sources of wood have gone out of business, he's requested a logging permit from the government. The government has granted him a permit for a row of trees near his house, and he'll use his newly purchased wood chipper to get the wood.

Here's how the wood chipper works. First, Sanggeun must specify a height H for the chipper. This will cause the saw blade to rise H meters above the ground. Then, it will cut down all the trees in a row. Therefore, trees taller than H will be cut above H, while shorter trees will not be cut. For example, let's say the heights of the trees in a row are 20, 15, 10, and 17. If Sanggeun specifies 15 as the height, the resulting heights will be 15, 15, 10, and 15, and he will take home a tree that is 5 meters long and a tree that is 2 meters long. (He will take home a total of 7 meters.) The heights that can be set for the chipper are positive integers or 0.

Sanggeun is very concerned about the environment, so he only takes home as much wood as he needs. Write a program to determine the maximum height the tree cutter can be set to so that he can take home at least M meters of wood.

## 輸入說明

The first line contains the number N of trees and the length M of the tree that Sanggeun wants to take home. (1 ≤ N ≤ 1,000,000, 1 ≤ M ≤ 2,000,000,000)

The second line contains the heights of the trees. Since the sum of the heights of the trees is always greater than or equal to M, Sanggeun can always take the wood he needs for his home. The height is a positive integer less than or equal to 1,000,000,000, or 0.

## 輸出說明

Outputs the maximum height that the cutter can be set to in order to take home a tree at least M meters tall.

## 範例輸入 #1

```
4 7
20 15 10 17
```

## 範例輸出 #1

```
15
```

## 範例輸入 #2

```
5 20
4 42 40 26 46
```

## 範例輸出 #2

```
36
```
