# l963. 座位(1)

## 內容

小明的老師很有特色，編座位表經常編到很複雜，小明常常看不清楚，請你編寫一段程序，協助他解決問題。

## 輸入說明

第一行為一個整數H，代表總共有多少個學生。


第二行為一個坐位長闊，格式為 "長 寬"。


第三行為一個整數T，代表接下來有T行。


接下來有T行，格式為 : " 人名A left/right/up/down 人名B" 表示人名A的上下左右各一方為人名B。


最後一行格式為 : "人名C left/right/up/down X" 求人名C的上下左右各一方第X個位是誰。

## 輸出說明

輸出只有一行，為一個人名，即輸入最後一行的答案。


如沒有人則輸出"-1"。

## 範例輸入 #1

```
25
5 5
5
alex up tom
mike up alex
william right karl
karl right steve
steve right alex
alex left 3
```

## 範例輸出 #1

```
william
```

## 範例輸入 #2

```
42
6 7
4
john down max
max left paul
paul left vincent
paul up tom
vincent up 3
```

## 範例輸出 #2

```
-1
```
