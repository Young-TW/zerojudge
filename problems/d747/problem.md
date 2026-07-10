# d747. 迷宮路徑

## 內容

在 N*N 的地圖中

求出座標 ( A , B ) → ( X , Y ) 的最短路徑 (只能上下左右走)

地圖中，以 " X " 代表牆壁，測資中四周都有牆壁

## 輸入說明

輸入只有一組測資
第一行有兩個數字N M( 1 ≦ N ≦ 1000 ， 1 ≦ M ≦ 500 )
N 代表 N*N 的地圖

M 代表接下來詢問求出座標 ( A , B )→ ( X , Y ) 的最短路徑的次數

接下來會有 M 行，每行上會有 4 個數字 A , B , X , Y  (1≦ A,B,X,Y ≦N)

## 輸出說明

請求出座標 ( A , B ) → ( X , Y )的最短路徑
如果本來就是牆壁的話，請輸出 "ERROR"(不包含"")
如果沒辦法到達的話，請輸出 "-1"(不包含"")

  012345678 
0XXXXXXXX
1X............
2XC...........
3X.............

C的位置代表 ( 2 , 1 )

## 範例輸入 #1

```
12 2
XXXXXXXXXXXX
X..........X
X..........X
X..........X
X..........X
X..........X
X..........X
X..........X
X..........X
X..........X
X..........X
XXXXXXXXXXXX
6 6 3 3
2 1 10 10
```

## 範例輸出 #1

```
6
17




/////////////////////
以下是第一筆的測資，放在提示那邊，會對不齊，就放在這了，請多見諒
30 10000
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X............................X
X.X..XXXXXXXXXXXXXXXXXX......X
X...X........X..........X....X
X.X..........X..........X.X..X
X...XXXXXXXXXXXXXXXXXXX.X.X.XX
X.X.....................X.X.XX
X...XX................X.X.X.XX
X.X..XXXXXXXXXXXXXXXXXX...X.XX
X...XX................X.....XX
X.X..........................X
X...XXXXXXXXXXXXXXXXXXX.X....X
X.X....X............X...X.X..X
X...XXXXXXXXXXXXXXXXXXX.X.X.XX
X.X.....................X.X.XX
X...X.................X.X.X.XX
X.X..XXXXXXXXXXXXXXXXXX...X.XX
X...X.................X.....XX
X.X..........................X
X..X..X.X...XXXXXX.X..X..XXXXX
X..X..X.X........X.X..X......X
X..X..X.XXXXXX...X.X..XXXXX..X
X..X..X.X........X.X..X......X
X..X..X.X...XXXXXX.X..X..XXXXX
X..X..X.X........X.X..X......X
X..X..................XXXXX..X
X..XXXXXXXXXXXXXXXXXXXX......X
X..XXXXXXXXXXXXXXXXXXXX..XXXXX
X...........XX...............X
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
```
