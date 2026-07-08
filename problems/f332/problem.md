# f332. 貝瑞的鐵線體積

## 內容

![image](ShowImage?id=1614)


My name is Barry Allen,and I am the fastest manalive.
To the outside world, I'm an ordinary forensic scientist, 
but secretly, with the help of my friends at S.T.A.R. Labs, 
I fight crime and find other meta-humans like me.
I hunted down the man who killed my mother, but in doing so,
I opened up our world to new threats.
And I am the only one fast enough to stop them.


I am The Flash!
                        ----------<閃電俠>貝瑞·艾倫


今天艾倫要打擊罪犯，他利用了鐵線高速旋轉，產生高速氣流，成功打敗敵人。


回到實驗室時，他回想起今天的事情：鐵線高速旋轉時，好像就像一個以軸為 $\color{black}{ y=0}\ $ 的一個物體，而鐵線就是一個函數圖形 $\color{black}{ y=f(x)}\ $ 。


今天 $\color{black}{ f(x)}\ $ 為多項式函數，鐵線端點在 $\color{black}{ x=a}\ $ 和 $\color{black}{ x=b}\ $ 上 $\color{black}{ (a<b)}\ $ ，求旋轉後的體積
-----------------------------------------------------------------------------------------------------
示意圖(未依原比例、原精準度)



![image](ShowImage?id=1812)

## 輸入說明

第一行有 $\color{black}{ t}\ $ 


接下來有 $\color{black}{ t}\ $ 筆資料


每筆資料第一行為多項式次數 $\color{black}{ n}\ $ 


第二行 $\color{black}{ 1 \sim n+1}\ $ 個數字為最高項到最低項的係數


第三行為端點 $\color{black}{ a,b}\ $ 


- $\color{black}{1≤t≤100}\ $ 
- $\color{black}{0≤n≤5}\ $ 
- $\color{black}{-10≤係數≤10,係數∈Z,最高係數≠0}\ $ 
- $\color{black}{-10≤a<b≤10;\ a,b∈Z}\ $

## 輸出說明

輸出鐵線高速旋轉後的體積


四捨五入到小數第 $\color{black}{ 2}\ $ 位

## 範例輸入 #1

```
3
0
1
-4 -2
0
9
-1 4
0
3
-3 10
```

## 範例輸出 #1

```
6.28
1272.35
367.57
```

## 範例輸入 #2

```
3
1
-5 -4
9 10
1
-10 2
-10 5
1
-8 0
-4 4
```

## 範例輸出 #2

```
8338.83
122710.61
8578.64
```

## 範例輸入 #3

```
3
5
-8 0 -8 0 -6 7
4 5
2
2 8 3
0 1
3
5 8 4 9
-10 -1
```

## 範例輸出 #3

```
895239610.20
210.91
75795399.04
```
