# d134. 00369 - Combinations

## 內容

為了呼應台灣電腦彩券的發行，我們特別推出跟組合有關的題目。以台灣的彩券來說，從46個球中取出6個，共有C(46,6)=9366819種組合。（中特獎的機率：1/936681989，夠低了吧！）給你：


1 <= N <=100,          and               1 <= M <=100,               and             M <= N


我們可以根據下面的公示算出從N個東西中取出M個東西的組合數：



![image](ShowImage?id=243)


你可以假設你的答案C不會超出 C++的 unsigned long long int 的範圍。

## 輸入說明

每筆測試資料一行，有2個正整數 N,M。 N=0，M=0代表輸入結束。每筆測試資料一行，有2個正整數 N,M。 N=0，M=0代表輸入結束。

## 輸出說明

以下列的格式輸出：


N things taken M at a time is C exactly.


請參考Sample Output。

## 範例輸入 #1

```
100 6
20 5
18 6
0 0
```

## 範例輸出 #1

```
100 things taken 6 at a time is 1192052400 exactly.
20 things taken 5 at a time is 15504 exactly.
18 things taken 6 at a time is 18564 exactly.
```
