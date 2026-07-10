# l417. 走地圖(3)

## 內容

續上題，l154. 走地圖(1)、l396. 走地圖(2)，這次除了有斜向功能外，還改變了不能執行的規則。


更改為將不能執行的執行到最後一步可執行，詳見範例#2，但即使更改了，該步仍然計為失敗執行。

## 輸入說明

第一行為一個整數T，代表接下來有T行。


接下來有T行，為地圖，詳見範例輸入。"x"為初始位置，長闊為T。


接下來有若干行，以EOF Error為結束，為"up/down/left/right/left oblique/right oblique/left  down oblique/right down oblique x(步數)"。 為向左/右/上/下/左斜/右斜 行走x步。


如果執行後超出地圖，則不會執行。

## 輸出說明

輸出有若干行，為每一執行成功的步數的坐標(x? y ?)。如果不能執行，則輸出"-1"。


接下來一行為最終坐標，格式:"最終坐標為x? y?"


接下來一行為 格式:"所有執行數/成功執行數/失敗執行數/成功執行百分比%"


百分比取小數點後一個位，若為正整數則不用。

## 範例輸入 #1

```
5
- x - - -
- - - - -
- - - - -
- - - - -
- - - - -
down 3
right 2
left up oblique 3
right down oblique 2
left down oblique 1
right up oblique 2
right up oblique 1
```

## 範例輸出 #1

```
x2 y4
x4 y4
x1 y1
x3 y3
x2 y4
x4 y2
x5 y1
最終坐標為x5 y1
7/7/0/100%
```

## 範例輸入 #2

```
5
- x - - -
- - - - -
- - - - -
- - - - -
- - - - -
down 3
right 2
left up oblique 3
right down oblique 2
left down oblique 1
right up oblique 4
```

## 範例輸出 #2

```
x2 y4
x4 y4
x1 y1
x3 y3
x2 y4
x4 y2
x5 y1
最終坐標為x5 y1
7/6/1/85.7%
```
