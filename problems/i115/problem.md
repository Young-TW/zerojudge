# i115. 尋找紙牌

## 內容

今天雨昕把編號$\color{black}{0、1、2、……、N-1}$的紙牌按順序順時針排成一圈，$\color{black}{N=5}$的case如下圖。


也就是對於每張牌$\color{black}{k}$，他的順時針方向那張是$\color{black}{k+1}$，逆時針那張是$\color{black}{k-1}$，除了$\color{black}{0}$和$\color{black}{N-1}$例外。



![image](ShowImage?id=2078)


首先定義任兩張牌$\color{black}{a}$、$\color{black}{b}$的距離$\color{black}{dist(a,b)}$代表$\color{black}{a}$從順時針或逆時針方向兩邊沿著圓到達$\color{black}{b}$，中間經過的距離的最小值，這裡定義兩個相鄰的紙牌之間距離$\color{black}{1}$，因此在$\color{black}{N=5}$時，也就是有五張紙牌時可以畫出上面那張圖，其中$\color{black}{dist(1,3)=min(2,3)=2}$、$\color{black}{dist(0,4)=min(1,4)=1}$，另外定義如果$\color{black}{a=b}$時，則$\color{black}{dist(a,b)=0}$，簡單來說距離的定義就是如果$\color{black}{a≥b}$，則$\color{black}{dist(a,b)=min(a-b,N-a+b)}$。


而現在雨昕在心裡選了其中一張牌，它的數字為$\color{black}{ans}$，阿祁要試著猜出雨昕的謎底，但是需要一些提示，所以阿祁每次可以選兩個數字$\color{black}{x}$、$\color{black}{y}$，雨昕會告訴阿祁$\color{black}{dist(x,ans)}$與$\color{black}{dist(y,ans)}$的大小關係，如果$\color{black}{dist(x,ans)}$比較小，雨昕會回答$\color{black}{x}$；反之如果$\color{black}{dist(y,ans)}$比較小，雨昕會回答$\color{black}{y}$，如果兩個$\color{black}{dist}$一樣他會說兩個一樣大。


阿祁現在要從$\color{black}{0、1、2、……、N-1}$裡找到雨昕的答案，但是他不會亂猜，要有把握才會作答，所以現在問你一件事，如果阿祁在完全不知道任何資訊下使用最聰明的方法玩，至少要先詢問幾次距離大小關係，才一定可以確定答案呢?

## 輸入說明

本題有多筆測資，因此第一行會有一個正整數$\color{black}{T}$告訴你有幾筆測資。


接著有$\color{black}{T}$行代表$\color{black}{T}$筆測資，每個測資都只有一行一個數$\color{black}{N}$，代表牌有$\color{black}{N}$張。


測資範圍:


$\color{black}{1 ≤ T ≤ 10^5}$


$\color{black}{2 ≤ N ≤ 10^{18}}$

## 輸出說明

針對每個測資，輸出一個數代表答案(也就是查詢所需最小次數)。

## 範例輸入 #1

```
8
2
3
4
5
6
7
8
9
```

## 範例輸出 #1

```
1
1
2
2
2
2
2
3
```
