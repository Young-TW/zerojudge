# e200. 金錢危機

## 內容

「欸，我錢包忘在樓上，可以幫我墊一下嗎？」


　　「拜託借我50塊，明天還你。」


　　「快點繳班費！！！！」


　　學生時期常常會有大家把錢借來借去的問題，可想而知，如果欠錢的人一直還沒還錢，卻一直有新的借據出現的話，整個借錢的關係只會越來越複雜。


　　金錢的流動越多，就越容易發生爭執和意外，為了減緩這件事情，你決定把大家的「還款圖」記錄下來，並試圖減少金錢的流量總量。


　　用明確一點的方式說明，現在有$\color{black}{\space N\space}$個人，並且有$\color{black}{\space M\space}$條還款關係，每條還款關係將會有$\color{black}{\space a,b,w\space}$三個正整數，代表編號$\color{black}{\space a\space}$的人還需要還編號$\color{black}{\space b\space}$的人$\color{black}{\space w\space}$塊錢。


　　你希望能構造出一個新的「還款圖」，使得每個人都沒有任何損失，而且金錢總流動量(也就是所有還款關係的還錢量總和)最少。

## 輸入說明

輸入首行有一個正整數$\color{black}{\space T(T\leq 20)\space}$，代表測資筆數。


每筆測資首行有兩個正整數$\color{black}{\space N,M(N,M\leq 10^5)\space}$如題目所述。


接下來$\color{black}{\space M\space}$行，每行三個整數$\color{black}{\space a,b,w(1\leq a,b\leq N,a\neq b,1\leq w\leq 10^4)\space}$，代表編號$\color{black}{\space a\space}$的人還需要還編號$\color{black}{\space b\space}$的人$\color{black}{\space w\space}$塊錢。

## 輸出說明

對於每筆測資，首行輸出一個$\color{black}{\space k\space}$，代表你重新構造完的圖有$\color{black}{\space k\space}$條邊，接下來$\color{black}{\space k\space}$行，每行三個正整數$\color{black}{\space a,b,w\space}$，你構造出來的圖中，編號$\color{black}{\space a\space}$的人還需要還編號$\color{black}{\space b\space}$的人$\color{black}{\space w\space}$塊錢。


你的輸出需要滿足對於每筆測資，有$\color{black}{\space k\leq max(M,N)\space}$且任意一條還款關係都有$\color{black}{\space 1\leq a,b\leq N,a\neq b,1\leq w\leq 10^9\space}$，當有任一項不符合，你將會獲得一個WA；否則對於任何一個還錢量總和是最佳解(最小值)的關係圖，你都能獲得AC。

## 範例輸入 #1

```
2
4 3
1 2 1
2 3 3
3 4 1
2 2
1 2 2
2 1 3
```

## 範例輸出 #1

```
3
1 3 1
2 3 1
2 4 1
1
2 1 1
```
