# e198. 課堂分組

## 內容

這天，特石想為他教導的$\color{black}{\space N\space}$個學生辦一場程式競賽，但不幸地是現在電腦教室正在進行校友盃(校友們都非常優秀，不方便打擾)，所以他們移駕到了另一間電腦分布很奇怪的電腦教室，這間教室所有電腦是連成一直線的，且不能移動位置；電腦們的編號為$\color{black}{\space 1\sim N\space}$，對於所有$\color{black}{\space 1<i<N\space}$，都滿足電腦$\color{black}{\space i\space}$的左邊是電腦$\color{black}{\space i-1\space}$、右邊是電腦$\color{black}{\space i+1\space}$。


　　學生們剛進教室就立刻全部坐定了位置，而且他們也不想再換位置，這時特石才發現，他忘記分組了，由於大家的實力不平均，盲目地亂分組只會導致隊伍不平衡，然而又不能讓不相鄰的學生同一組，這讓特石非常困擾。


　　已知坐在電腦$\color{black}{\space i\space}$的學生的實力值是$\color{black}{\space p_i\space}$，且特石訂定出了一組的誤差值計算方式，也就是該組所有學生的實力值總和與$\color{black}{\space K\space}$的絕對值再加上$\color{red}{\space X\space}$，你能夠告訴他，在最佳的分組方式下，每一組的誤差值總和最小可以是多少嗎？

## 輸入說明

輸入首行有一個正整數$\color{black}{\space T(T\leq 20)\space}$，代表測資筆數。


每筆測資首行有三個整數$\color{black}{\space N,K,X(1\leq N\leq 10^5,1\leq K \leq 10^9,0\leq X\leq 10^9)\space}$，意義如題目所述。


次行有$\color{black}{\space N\space}$個正整數$\color{black}{\space p_1\sim p_N(1\leq p_i\leq 10^4)\space}$，代表編號$\color{black}{\space i\space}$的學生的實力值為$\color{black}{\space p_i\space}$。

## 輸出說明

對於每筆測資，輸出在最佳的分組方式下，每一組的誤差值總和最小可以是多少。

## 範例輸入 #1

```
2
5 3 1
3 1 4 2 5
5 5 1
3 1 4 2 5
```

## 範例輸出 #1

```
9
5
```
