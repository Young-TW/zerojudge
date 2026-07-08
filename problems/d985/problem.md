# d985. Gran Turismo 5

## 內容

最近，

 學姊籌錢買了一片 Gran Turismo 5 回家做賽車夢，

 又另外買了 G27 方向盤，

 但在賽車場上的表現始終不如人意。

  
![image](ShowImage?id=437)

 "車，不是這麼開的。"

 說完爸爸接過了方向盤，

 將記錄一次又一次的刷新。

 給你每一圈的時間紀錄，

 請算出 Best Lap 與平均時間。

 我一定要成為車神！

## 輸入說明

第一行有一個數字 N (0 < N ≤ 10)

 代表接下來有 N 組測試資料

 每組測試資料第一行有一個數字 M (0 < M ≤ 100)

 接著有 M 行資料

 每行兩個數字 A, B (0 ≤ A, B ≤ 60)

 代表該圈所花費時間為 A 分 B 秒

## 輸出說明

Track X:

 Best Lap: X minute(s) X second(s).

 Average: X minute(s) X second(s). 

 Average 為整數，小數部份無條件捨去

 詳請參考範例測資

## 範例輸入 #1

```
3
4
1 54
2 02
1 58
1 50
3
1 23
1 42
1 37
5
3 00
2 56
3 04
2 50
3 01
```

## 範例輸出 #1

```
Track 1:
Best Lap: 1 minute(s) 50 second(s).
Average: 1 minute(s) 56 second(s).

Track 2:
Best Lap: 1 minute(s) 23 second(s).
Average: 1 minute(s) 34 second(s).

Track 3:
Best Lap: 2 minute(s) 50 second(s).
Average: 2 minute(s) 58 second(s).
```
