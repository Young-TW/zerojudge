# c708. 11538 - Chess Queen

## 內容

給一個棋盤求兩隻相異(西洋棋)皇后能互相攻擊的擺放位置數


注：西洋棋皇后移動方式為直、橫、對角線任意格 


 


原題有附第一筆測資的圖片，看不懂得可以參考看看


https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2533


 


* 2022/02/26 測資加強並重測所有AC code

## 輸入說明

棋盤長寬 $n,m$ ($n,m\leq 10^6$)


以 $0\,0$ 結尾，此筆不須輸出


至多 $5000$ 筆測資，並且保證答案可以用long long int儲存

## 輸出說明

如題

## 範例輸入 #1

```
2 2
100 223
2300 1000
0 0
```

## 範例輸出 #1

```
12
10907100
11514134000
```
