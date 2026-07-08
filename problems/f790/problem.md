# f790. 勝利的五子棋

## 內容

有一個7*7的棋盤


裡面含有白棋(o)以及空地(x),沒有黑棋


輸出白棋是否形成以下陣形:


-------------------------------------------------------------------------------------------------------------------------------------------------------


xxxxxxx        xxxxxxx
xxxxxxx        xxxxxxx
xxxoxxx        xxxxoxx  
xxxoxxx        xxxoxxx               三顆白棋以直線或斜線相連，且兩端皆為空地,稱為"活三"    
xxxoxxx        xxoxxxx 
xxxxxxx        xxxxxxx  
xxxxxxx        xxxxxxx         


 


xxxxxxx        xxxxxxx
xxxxxxx        xxxxxxx
xxxxxxx        xxxxoxx  
xxooxox        xxxxxxx               同一直線或斜線上的三顆白旗，中間空一格,且兩端皆為空地，也稱為"活三"    
xxxxxxx        xxoxxxx 
xxxxxxx        xoxxxxx  
xxxxxxx        xxxxxxx  


------------------------------------------------------------------------------------------------------------------------------------------------------


xxxxxxx        xxxxxxx
xxxoxxx        xxxxxxx
xxxoxxx        xxxxoxx
xxxoxxx        xxxoxxx                  四顆白棋以直線或斜線相連，且兩端皆為空地，稱為"活四"
xxxoxxx        xxoxxxx
xxxxxxx        xoxxxxx
xxxxxxx        xxxxxxx


------------------------------------------------------------------------------------------------------------------------------------------------------


xxxoxxx        xxxxxxx
xxxoxxx        xxxxxxx
xxxoxxx        xxxxxxx
xxxoxxx        xxxoxxx                  四顆白棋以直線或斜線相連，且只有其中一端為空地，稱為"死四"
xxxxxxx        xxoxxxx
xxxxxxx        xoxxxxx
xxxxxxx        oxxxxxx


-------------------------------------------------------------------------------------------------------------------------------------------------------


註: 直線包含直的線和橫的線

## 輸入說明

輸入為一個7*7圖形


(每組輸入的每種陣型最多只會出現十個，有可能沒有出現)

## 輸出說明

輸出圖形內包含哪些陣形


輸出的順序為死四>活四>活三


如果單一陣形出現一個以上，請用"雙"或國字"參" "肆" "伍" "陸" "柒" "捌" "玖" "拾"，只有一個則不用標明

## 範例輸入 #1

```
xxxxxxx
xxxxxxx
xxoxxxx
xxoxxxx
xxoxxxx
xxxxxxx
xxxxxxx
```

## 範例輸出 #1

```
活三
```

## 範例輸入 #2

```
xxxxxxx
xoxxxxx
xxoxxxx
ooooxxx
xxxxxxx
xxxxxxx
xxxxxxx
```

## 範例輸出 #2

```
死四活三
```

## 範例輸入 #3

```
xxxxxxx
xxxxxxx
xoxxxxx
xxoxoxx
xooooxx
xxoxoxx
xxoxxxx
```

## 範例輸出 #3

```
死四雙活四雙活三
```
