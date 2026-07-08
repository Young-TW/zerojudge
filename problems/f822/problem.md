# f822. 紅林愛下棋

## 內容

[難度 🌕🌕🌕🌕🌗]


紅林是一個愛好圍棋的人，每次他在某方面贏不了別人時，總會說「來比圍棋啊!」


但他圍棋非常廢，贏不了別人，於是我們要幫他判斷一下現在是誰贏或輸。


 


(圍棋是9*9棋盤


只需比誰的地盤大)

## 輸入說明

單筆輸入，輸入9*9棋盤

## 輸出說明

if 沒下完(有地盤同時被W和B圍著)，輸出"Wrong"即可


else {


輸出誰贏(Black wins!!)(White wins!!)


輸出B與W地盤比數


輸出B與W的地盤


}

## 範例輸入 #1

```
.........
.B.....B.
BBB....BB
BBBBBBBBB
WWWWWWWWW
WWW..WWWW
WWWWWWWBB
.....WBB.
.....WB.B
```

## 範例輸出 #1

```
Black wins!!
44:37
BBBBBBBBB
BBBBBBBBB
BBBBBBBBB
BBBBBBBBB
WWWWWWWWW
WWWWWWWWW
WWWWWWWBB
WWWWWWBBB
WWWWWWBBB
```

## 範例輸入 #2

```
.........
.B.....B.
BBB....BB
BBBBBBBBB
WWWW.WWWW
WWW..WWWW
WWWWWWWBB
......WB.
......WBB
```

## 範例輸出 #2

```
Wrong
//中間那塊被B和W圍著(此行不須輸出)
```
