# c718. 路上的詛咒

## 內容

$\color{black}{\space bert \space}$所在的世界是由$\color{black}{\space N \space}$個點和$\color{black}{\space N-1 \space}$條道路互相連結而成的，而且保證這些點可以互相直接或間接通過這些道路往來。


　　$\color{black}{\space bert \space}$常常接到遠征任務，當他每次接到任務時，他會從所在編號是$\color{black}{\space S \space}$的點，出發到任務目標所派遣到的編號是$\color{black}{\space T \space}$的點遠征，遠征完後再原路返回。但事實上遠征並沒有很簡單，每條道路上都會有敵國所佈下的詛咒(沒錯，他們不直接攻打別人)，路途上的詛咒必須自己承擔，而每種詛咒都有自己的強度，但$\color{black}{\space bert \space}$也不是好惹的，他每次出征前都會準備不同的防禦用品使他的防禦力變成$\color{black}{\space d \space}$，所以當$\color{black}{\space bert \space}$受到了強度$\color{black}{\space h_i \space}$的詛咒，如果$\color{black}{\space h_i>d \space}$，他就會受到$\color{black}{\space v_i \space}$點量值的傷害，否則他可以完整的抵擋這次詛咒。


　　現在你清楚傷害的計算方式了，$\color{black}{\space bert \space}$在給了你道路資訊的同時想多次麻煩你，當他在點$\color{black}{\space S \space}$接到點$\color{black}{\space T \space}$的遠征任務時，若他的防禦力是$\color{black}{\space d \space}$，他將會受到多少傷害量值呢？由於去程跟回程的傷害是一樣的，所以你只需要計算去程的答案就好了。


　　噢對了，由於敵國的詛咒是不斷在更新的，所以在$\color{black}{\space bert \space}$的多次詢問當中也會穿插多次的道路詛咒修改。

## 輸入說明

首行有兩個正整數$\color{black}{\space N,Q(1\leq N,Q\leq 10^5) \space}$，代表點的個數和$\color{black}{\space bert \space}$詢問加上修改的總次數。


接下來$\color{black}{\space N-1 \space}$行，第$\color{black}{\space i+1(1\leq i<N) \space}$行有四個正整數$\color{black}{\space a_i,b_i,h_i,v_i(1\leq a_i,b_i,h_i\leq N,1\leq v_i \leq 10^9) \space}$代表第$\color{black}{\space i \space}$條道路連接點$\color{black}{\space a_i,b_i \space}$，且詛咒強度為$\color{black}{\space h_i \space}$，傷害值為$\color{black}{\space v_i \space}$。


接下來$\color{black}{\space Q\space}$行，每行代表一個操作，如果是$\color{black}{\space 0\space S\space T\space d(1\leq S,T\leq N,S\not=T,0\leq d\leq N) \space}$，代表$\color{black}{\space bert \space}$在點$\color{black}{\space S \space}$，他接到點$\color{black}{\space T \space}$的遠征任務，他的防禦力是$\color{black}{\space d \space}$；如果是$\color{black}{\space 1\space x\space h\space v(1\leq x<N,1\leq h\leq N,1\leq v\leq 10^9)\space}$，代表編號$\color{black}{\space x \space}$的道路的詛咒強度被更新成$\color{black}{\space h \space}$、傷害值被更新成$\color{black}{\space v \space}$了。

## 輸出說明

對於每個遠征任務的詢問，輸出$\color{black}{\space bert \space}$將會受到多少傷害量值於一行。

## 範例輸入 #1

```
6 5
1 2 3 7
1 3 1 3
3 4 5 2
3 5 4 5
3 6 2 8
0 1 4 2
0 2 6 2
1 2 4 4
0 1 4 2
0 2 6 2
```

## 範例輸出 #1

```
2
7
6
11
```
