# j540. Wordle

## 內容

<Wordle> 是喬什·沃德爾（Josh Wardle）所設計的網頁單字遊戲，玩家每日可挑戰在六次嘗試內，猜出由五個字母所組成的英文單詞。



![image](ShowImage?id=2676)


如圖，綠色代表字母位置對 ; 黃色字母代表答案有這個字母但是位置錯誤 ; 灰色字母代表答案沒有出現這個字母。在本題，綠色以O表示，黃色以Y表示，灰色以X表示。請寫一個程式，輸入玩家猜的單字，並輸出玩家猜的結果。


- 若有字母在對的位置，則優先輸出，請見範例測資。
- 否則優先處理前面的字母

## 輸入說明

第一行輸入一字串 S ( S固定為5個字母，且均為大寫)。第二行輸入一整數p (p<=50000), 表示今天有多少人挑戰。接下來每行輸入字串 t ，表示玩家所猜的單字。


每一個人的猜測以 "#"作為結束。

## 輸出說明

輸出玩家猜的結果。若玩家猜的單字太短，請輸出 "Not enough letters"  ; 若玩家猜的單字太長，輸出 "Too long"; 若玩家猜中了，則在輸出結果後換行輸出 "Congradulat1ons ! You guessed n times"(n為玩家猜的數量); 若玩家已經猜中過了，則該行不輸出。玩家猜完後請空一行。


*上述輸出均不含引號


*單字太長或太短都不算一次

## 範例輸入 #1

```
OPERA
3
APPLE
BANANA
STEAL
#
OPERA
KKKKKK
#
OPERN
OPER
#
```

## 範例輸出 #1

```
YOXXY
Too long
XXOYX

OOOOO
Congradulat1ons ! You guessed 1 times

OOOOX
Not enough letters
```

## 範例輸入 #2

```
XXOOL
2
IXJDC
BPRAE
#
OXOXL
OOOXL
#
```

## 範例輸出 #2

```
XOXXX
XXXXX

YOOYO
YXOYO
```
