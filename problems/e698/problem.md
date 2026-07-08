# e698. OREOREO!

## 內容

有一種叫「OREO」的餅乾


黑色的部分叫「O」


白色的部分叫「RE」


現在給你一片餅乾，請你印出這片餅乾



![image](ShowImage?id=1421)

## 輸入說明

總共有多組輸入


每組輸入前兩行分別是O和RE的寬高和成分(O和RE的寬奇偶數相同)


再來輸入一個數字n，代表有n片餅乾要你印出來


1≤O,RE的寬和高≤100


1≤n≤100


1≤O+RE的數量≤100

## 輸出說明

由上到下輸出餅乾的每個部份，寬比較短的要置中輸出


本題採嚴格比對，後面勿有多餘空白


測資後要空行


(如果還是不確定格式可參考範例)

## 範例輸入 #1

```
5 3
3 4
- o
3
OREO
REORERE
OOORE
5 4
9 2
: .
2
OREREREO
REOOOREO
```

## 範例輸出 #1

```
-----
-----
-----
 ooo
 ooo
 ooo
 ooo
-----
-----
-----

 ooo
 ooo
 ooo
 ooo
-----
-----
-----
 ooo
 ooo
 ooo
 ooo
 ooo
 ooo
 ooo
 ooo

-----
-----
-----
-----
-----
-----
-----
-----
-----
 ooo
 ooo
 ooo
 ooo

  :::::
  :::::
  :::::
  :::::
.........
.........
.........
.........
.........
.........
  :::::
  :::::
  :::::
  :::::

.........
.........
  :::::
  :::::
  :::::
  :::::
  :::::
  :::::
  :::::
  :::::
  :::::
  :::::
  :::::
  :::::
.........
.........
  :::::
  :::::
  :::::
  :::::

```

## 範例輸入 #2

```
6 2
4 3
H I
5
OO
REO
ORERE
REORE
OOOREO
```

## 範例輸出 #2

```
HHHHHH
HHHHHH
HHHHHH
HHHHHH

 IIII
 IIII
 IIII
HHHHHH
HHHHHH

HHHHHH
HHHHHH
 IIII
 IIII
 IIII
 IIII
 IIII
 IIII

 IIII
 IIII
 IIII
HHHHHH
HHHHHH
 IIII
 IIII
 IIII

HHHHHH
HHHHHH
HHHHHH
HHHHHH
HHHHHH
HHHHHH
 IIII
 IIII
 IIII
HHHHHH
HHHHHH

```
