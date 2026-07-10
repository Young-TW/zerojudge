# d365. 10336 - Rank the Languages

## 內容

你可能有注意到世界上有許多地區使用英語及西班牙語。現在我們就要來對世界上所有地區使用的語言作個排行榜。

你會給一個地圖，在上面會標示各地區以幾他們所使用的語言。請看以下的地圖：

ttuuttdd 
ttuuttdd 
uuttuudd 
uuttuudd  每個字元代表一種語言，並且區域被定義為同一個字元相連的地區。2個字元"相連"指的是該2字元有上、下、左、右四個方向鄰近的關係。所以在上圖中有3個區域說 t 語言，有3個區域說 u 語言，有1個區域說 d 語言。

你的任務就是要找出地圖中每種語言被說的區域數，並且按照一定的順序輸出。

## 輸入說明

輸入的第一列有一個整數 N

代表以下有幾組測試資料

每組測試資料的第一列有 2 個整數 H 及 W 

代表此地圖的高度及寬度

接下來的 H 列每列有 W 個字元

所有的字元均為小寫的英文字（a~z）

## 輸出說明

對每組測試資料

先輸出 "World #n"

n 是第幾組測試資料

接下來輸出在此地圖中每種語言被說的區域數 (請由大到小排列)

如果有2種語言區域數相同

請依英文字的順序輸出 (例如i語言要在q語言之前)

請參考 Sample Output

## 範例輸入 #1

```
2
4 8
ttuuttdd
ttuuttdd
uuttuudd
uuttuudd
9 9
bbbbbbbbb
aaaaaaaab
bbbbbbbab
baaaaacab
bacccccab
bacbbbcab
bacccccab
baaaaaaab
bbbbbbbbb
```

## 範例輸出 #1

```
World #1
t: 3
u: 3
d: 1
World #2
b: 2
a: 1
c: 1
```
