# c626. 貪食蛇 #1  ( 穿牆不可 )

## 內容

這是很多人玩過的經典遊戲，大家來重溫一下。

## 輸入說明

每個測資有一個 w = 21 , h = 15 的格子。
每個格子中：
s 是剛出生的小蛇，位於 x = 0 , y = 0
o 是空格
$ 是食物，吃了之後 snake 會變長。
x 是障礙物，會阻止前進。
snake 無法翻出牆外。
snake 也無法跨越自己的身體。
最下方一列是方向及預計走的步數。
snake 不一定能走完所有的步數。

## 輸出說明

請輸出 snake 停止時，
從頭到尾的座標。
x y

## 範例輸入 #1

```
s$oooooooooo$oo$ooooo
oo$$o$oooxoo$oooo$o$o
$ooooo$oooxooooooo$oo
oooooo$oooo$ooo$ooooo
ooooooo$ooxo$o$oooooo
$oooo$oooxoo$ooo$$ooo
o$oooooooooo$oooooooo
ooo$ooo$ooxo$ooooxooo
ooooo$oooooooooo$oooo
ooooooo$o$oooo$oooooo
$oooxo$o$oooooooooooo
$o$ooooooooooooooxxoo
oo$oo$$ooooo$ooooo$oo
oooxooo$$o$oooooooooo
ooooo$oo$oooooooo$o$o
E 3 S 1 W 11 N 4 W 5
```

## 範例輸出 #1

```
0 1
1 1
2 1
3 1
```
