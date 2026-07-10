# d364. 10637 - Coprimes

## 內容

How many times must a man look up
Before he can see the sky?
Yes, 'n' how many ears must one man have
Before he can hear people cry?
Yes, 'n' how many deaths will it take till he knows
That too many people have died?
The answer, my friend, is blowin' in the wind,
The answer is blowin' in the wind.

在一個陰暗的天氣，如同往常的，Shahriar的CD中傳來這首希望的歌曲。在他的面前有一大堆紙張，他嘗試用手在上面寫出把一個數分割成一些互質（co-prime）的數的所有可能。當然可想而知，最後一定無法用手算出答案。於是他想要寫一個程式來做這件事，但是他的程式能力不太行，所以他請求你的幫忙。

在一些數中，如果任2個數的最大公因數（GCD） 都是 1 ，那麼我們稱這些數互質。

## 輸入說明

輸入的第一列有一個正整數 N < 40 代表有多少組測試資料

每組測試資料一列，有 2 個正整數 S（0 < S <= 100）和 t（0 < t <= 30）

## 輸出說明

對每組測試資料先輸出這是第幾組測試資料

接下來的每列為一種把 S 分割成 t 個互質的正整數的方法

在每個方法中的數請由小到大輸出

若有多種方法可以分割

輸出的順序則依照類似字典順序

請參考Sample Output

## 範例輸入 #1

```
4
40 6
8 3
5 2
3 1
```

## 範例輸出 #1

```
Case 1:
1 1 1 1 1 35
1 1 1 1 5 31
1 1 1 1 7 29
1 1 1 1 11 25
1 1 1 1 13 23
1 1 1 1 17 19
1 1 1 3 5 29
1 1 1 3 11 23
1 1 1 5 9 23
1 1 1 5 11 21
1 1 1 5 13 19
1 1 1 7 11 19
1 1 1 7 13 17
1 1 1 9 11 17
1 1 3 5 7 23
1 1 3 5 11 19
1 1 3 5 13 17
1 1 3 7 11 17
1 1 5 7 9 17
1 1 5 9 11 13
1 3 5 7 11 13
Case 2:
1 1 6
1 2 5
1 3 4
Case 3:
1 4
2 3
Case 4:
3
```
