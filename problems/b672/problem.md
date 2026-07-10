# b672. A Special Automobile Race

## 內容

There is a special automobile race. The race do not care about who can drive fast, but care about who is good in math. There are n rest stations before terminal point. If a player wants to stay in a rest station, he must change an automobile in that rest station. The automobiles in diferent rest stations can run diferent distances. For example, if the distance is 3, the automobile will be able to run to at least next 3 rest stations.


The winner is the player who has stayed the least number of rest stations. Now Bob wants to know how many rest stations are needed to win the race. Write a program to help Bob find the minimum number of rest stations that are needed.

## 輸入說明

The input contains several test cases. Each input contains two lines. The first line contains an integer. The integer denotes the number of total rest stations n. The value of n is between 1 and 200000. The second line has n integers. Every integer denotes the distance that the automobile in that rest station can run. Each input in this line is between 1 and 20.


Furthermore, for each input, we suppose that the automobile in the starting point can run to at least next 5 rest stations. The last line of input is only one 0 indicating the end of input.

## 輸出說明

For each input data, print the minimum number of rest stations that are needed.

## 範例輸入 #1

```
4
4 4 4 4
5
5 4 3 2 1
6
1 1 1 1 1 1
8
4 4 4 4 1 1 1 1
10
10 8 6 4 2 5 4 3 2 1
20
5 5 5 2 2 5 5 5 2 2 5 5 5 2 2 3 3 3 1 1
0
```

## 範例輸出 #1

```
0
1
2
2
1
4
```
