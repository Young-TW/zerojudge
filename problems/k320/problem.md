# k320. 勝差

## 內容

有一個職業聯盟的戰績表很奇怪，給你勝差，已賽場數，近十場戰績，連勝狀況 ... 就是不給你球隊幾勝幾敗 !


請寫一個程式，把它算出來。


* 例行賽不會有和局

## 輸入說明

多筆輸入


每筆測梔會先輸入一整數 n (2<=n<=100) 代表此職業聯盟共幾隊


接下來有n行，每行輸入一字串 s 表示隊名，再輸入 g ，gs，分別表示已賽場數，與第一名的勝差。

## 輸出說明

每行輸出隊名，勝場數，敗場數 (見範例)


若此戰績表不存在，請輸出 "establish" (不含引號)

## 範例輸入 #1

```
5
Rakuten 9 0
Dragons 11 0
Guardians 10 0.5
Brothers 11 1
Unilions 9 1
```

## 範例輸出 #1

```
Rakuten 5W4L
Dragons 6W5L
Guardians 5W5L
Brothers 5W6L
Unilions 4W5L
```

## 範例輸入 #2

```
5
Rays 16 0
Yankees 16 0
Toronto 16 0
Baltimore 15 0
Redsox 17 0
```

## 範例輸出 #2

```
establish
```
