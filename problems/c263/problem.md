# c263. 趙哥愛妹子

## 內容

趙哥是一個癡漢。
他想要把他中意的所有妹子通通抓起來，為了使抓起來的妹子們無法互相往來(這樣才能夠玩$\color{black}{\space 1\space}$對$\color{black}{\space 1\space}$小遊戲，妹子也不會一起串通逃跑)，他必須將他的土地分成若干個1平方單位的房間給各個妹子住$\color{black}{\space(1\leq n,m\leq 40)\space}$。



他為了達到此目的，花了他一生的積蓄，還付出了他死後的軀體跟剩餘人生50%的壽命請求森大人教他造牆術。



以下是造牆術的規則:
1.先尋找一個點$\color{black}{\space x\space}$ (介於$\color{black}{\space (1,1)\sim (n,m)\space}$)。
2.尋找點$\color{black}{\space x\space}$所需的魔法能量。
3.將點$\color{black}{\space x\space}$跟該點的不斷延伸前後左右所形成的十字，對每個點蓋出與魔法能量等高的牆，每個方向都一直延伸直到撞到整個空間的邊緣或是其他牆壁。
4.此術所消耗的總魔法能量會等於所有有造牆的點的魔法能量乘上點$\color{black}{\space x\space}$的魔法能量



趙哥為了能在蓋完房間後能與妹子們曬恩愛，他希望他能夠盡量消耗最少的能量蓋完所有房間的牆，請你幫他求出這個最少能量是多少。

## 輸入說明

第一行輸入兩個變數$\color{black}{\space n,m\space}$
代表趙哥要蓋$\color{black}{\space n\times m\space}$個牆造出若干個房間
從第二行到第$\color{black}{\space n+1\space}$行各輸入$\color{black}{\space m\space}$個變數
代表每一個點所需的魔法能量(每個點的魔法能量$\color{black}{\space \leq 10^7\space}$)

## 輸出說明

請輸出趙哥所需消耗最少的魔法能量


PS:
最終趙哥終於蓋好了房間，然後興高采烈地去抓了妹子。
但他突然發現...
他不過就是一個且連一個妹子都抓不到就被法律制裁的沒人要的巨乳控QQ。

## 範例輸入 #1

```
Input1:
1 1 
100

Input2
2 3
3 6 4
5 4 9
```

## 範例輸出 #1

```
Output1:
10000

Output2:
106
```
