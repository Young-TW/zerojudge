# c983. 驚殘好夢無尋處

## 內容

$\color{black}{\space alan \space}$很愛睡覺，為了防止自己睡過頭，他每天都設定了$\color{black}{\space N \space}$個鬧鐘，都在固定的時間啟動，響一單位時間然後停止，而第$\color{black}{\space i\space}$個鬧鐘會在$\color{black}{\space t_i \space}$單位時間時響起。可是明天是放假日，$\color{black}{\space alan \space}$為了睡好睡滿睡一整天，需要關掉一些鬧鐘。他知道，如果在任意連續的$\color{black}{\space M \space}$單位時間內，存在不小於$\color{black}{\space K \space}$個鬧鐘響起，他就會醒來。


　　不過這些鬧鐘可不單純，除了大眾一般的鬧鐘，其中還參雜著進化版的睡你妹鬧鐘、怪物鬧鐘、火箭鬧鐘等等棘手的鬧鐘，由於$\color{black}{\space alan \space}$平常時間的防範心太強了，這些鬧鐘就連取消設定都很費力，其中第$\color{black}{\space i\space}$個鬧鐘必須要花$\color{black}{\space p_i\space}$的力氣才能關閉。


　　為了早點睡覺，$\color{black}{\space alan \space}$想要知道最少要花多少力氣才能確保明天不會被鬧鐘吵醒。

## 輸入說明

輸入首行有一個正整數$\color{black}{\space T(T\leq 20) \space}$，代表共有$\color{black}{\space T \space}$筆測資。


每筆測資共有三行，首行有三個正整數$\color{black}{\space N,M,K(M\leq 10^9,K\leq 100, N\leq 1000) \space}$，代表$\color{black}{\space alan \space}$設定了$\color{black}{\space N \space}$個鬧鐘，如果在$\color{black}{\space M \space}$單位時間內有$\color{black}{\space K \space}$單位時間有鬧鐘響起，他就會醒來。


次行有$\color{black}{\space N \space}$個正整數$\color{black}{\space t_1\sim t_N(1\leq t_i\leq 10^9) \space}$，代表第$\color{black}{\space i \space}$個鬧鐘會在$\color{black}{\space t_i \space}$單位時間時響起。


末行有$\color{black}{\space N \space}$個正整數$\color{black}{\space p_1\sim p_N(1\leq p_i\leq 10^5) \space}$，代表第$\color{black}{\space i \space}$個鬧鐘必須要花$\color{black}{\space p_i \space}$的力氣才能關閉。


 


你可以假設一天有無限多單位時間，且所有$\color{black}{\space t_i \space}$兩兩相異。

## 輸出說明

對於每筆測資，輸出$\color{black}{\space alan \space}$最少要花多少力氣才能確保明天不會被鬧鐘吵醒。

## 範例輸入 #1

```
2
10 5 4
1 2 3 4 5 6 7 8 9 10
4 4 4 6 6 6 6 6 4 4
10 5 3
1 2 3 4 5 6 7 8 9 10
4 4 4 6 6 6 6 6 4 4
```

## 範例輸出 #1

```
20
30
```
