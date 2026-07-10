# c625. 貪食蛇 #2  ( 穿牆版 )

## 內容

這是很多人玩過的經典遊戲，大家來重溫一下。

## 輸入說明

每個測資有一個 w = 21 , h = 15 的格子。
每個格子中：
s 是剛出生的小蛇，位於 x = 0 , y = 0
o 是空格
$ 是食物，吃了之後 snake 會變長。
x 是障礙物，會阻止前進。
snake 無法跨越自己的身體。
最下方一列是方向及預計走的步數。
snake 不一定能走完所有的步數。

## 輸出說明

請輸出 snake 停止時，
從頭到尾的座標。
x y

## 範例輸入 #1

```
soo$o$o$oooooooo$ooxo
o$oxo$oooooo$$ooooooo
o$ooo$oxoooooooooo$oo
ooooooooooooooo$ooo$o
oooooox$oooo$oooooo$$
ooooooo$oxxooo$oooooo
oooooooooooooooo$oooo
ooooooo$$ooo$oooo$ooo
ox$oooooooooooxo$ooxx
ooooooo$ooooooooooooo
ooo$$$$o$ooooooooooo$
$o$oooooooooo$oooooo$
ooo$ooooooo$oo$oooooo
oo$ooo$oo$$ooooo$oooo
$o$ooo$ooooooo$ooo$oo
N 1 W 9 S 10 W 28 S 12 W 17
```

## 範例輸出 #1

```
9 6
10 6
11 6
12 6
13 6
14 6
15 6
16 6
17 6
18 6
19 6
20 6
0 6
```
