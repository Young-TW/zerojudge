# b595. Special Touring Car Racing

## 內容

Touring car racing is a car racing competition with heavily modified road-going cars. Most of the game is based on speed to determine the winner. A special touring car race to be held, the rules of this game is very special. The contestants need to rely on the wisdom to win the game.


All contestants start on the road at mile post 0. Along the way there are n parking areas, numbered as 1 <= i <= n, at mile posts a1< a2< . . . < an, where each ai is measured from the starting point. The only places the contestants are allowed to stop are at these parking areas, but they can choose which of the parking areas they stop at. The contestants must stop at the final parking area (at distance an), which is the destination.


The cars are specially designed, so that they would ideally drive 200 miles a day. This may not be possible, because of depending on the spacing of the parking areas. If the contestants drive x miles during a day, the penalty for that day is (200 - x)2. Minimum the sum of the daily penalties of contestant is the winner.


Jonathan wants to participate in this touring car race. Can you help him to win the game?

## 輸入說明

The input contains several test cases. Each test case has two lines. The first line contains the number of parking areas n. Here n <= 30. The second line contains n integers indicating the values of a1, a2, . . . , an. The values of a1, a2, . . . , an would be integers between 1 and 10000.


The last line of input is only one 0 indicating the end of input.

## 輸出說明

For each test case, output the parking areas at which to stop. The output starts at 0 and shows the parking areas numbers you stop at in order. The output of each test case should be in a separate line.

## 範例輸入 #1

```
4
190 260 385 540
5
130 180 230 330 450
0
```

## 範例輸出 #1

```
0 1 3 4
0 3 5
```
