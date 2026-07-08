# f981. P = NP

## 內容

- $\color{black}{0 = 0}\ $
$\color{black}{0*1 = 0*N}\ $
$\color{black}{1 = N}\ $
$\color{black}{1*P = N*P}\ $
$\color{black}{P = NP}\ $

caido 在算出世界難題後拿去給老師看，老師大吃一驚，覺得 caido 是可造之材，於是給他一個簡單的題目，就是一元二次方程式 $\color{black}{Ax^2+Bx+C=0\  (A≠0)}\ $，只是 $\color{black}{A, B, C}\ $ 是複數


請你計算出 $\color{black}{x}\ $

## 輸入說明

多筆輸入，每筆輸入有三行


依序是 $\color{black}{A, B, C}\ $


每行有兩實數 $\color{black}{a,b}\ $，代表 $\color{black}{a+bi}\ $


- $\color{black}{a,b}\ $ 為 $\color{black}{2}\ $ 位小數
- $\color{black}{-100≤ a,b ≤100}\ $

## 輸出說明

輸出 $\color{black}{x}\ $ 的解


若為重根，輸出 $\color{black}{the\ only\ x\ =\ ans}\ $


若有兩相異根，輸出 $\color{black}{first\ x\ =\ ans_1,\ second\ x\ =\ ans_2}\ $，$\color{black}{ans_1\ 和\ ans_2}\ $ 實部較小的先輸出，若實部相同，則比較虛部


若無解，輸出 $\color{black}{Xx}\ $


$\color{black}{ans}\ $ 要用 $\color{black}{a+bi}\ $ (or $\color{black}{a-bi}\ $) 表示


數字要四捨五入到小數第 $ \color{black}{2}\ $ 位


這一題請先比較數字大小再四捨五入


$\color{black}{Ex：}\ $


- $\color{black}{12.345→ 12.35，12.344→ 12.34}\ $
$\color{black}{0.005→ 0.01，0.004→ 0.00}\ $
$\color{black}{-12.345→ -12.35，-12.344→ -12.34}\ $
$\color{black}{-0.005→ -0.01，-0.004→ 0.00}\ $

詳見範例輸出

## 範例輸入 #1

```
-1.00 0.00
4.60 -14.00
43.71 32.20
26.41 56.63
72.20 72.65
-29.71 -44.80
-1.00 0.00
3.40 -7.40
10.80 12.58
-1.00 0.00
7.40 -6.20
-4.08 22.94
25.03 -48.73
-90.07 -92.53
-71.80 3.71
94.81 -39.49
32.44 -0.88
25.67 -8.62
```

## 範例輸出 #1

```
the only x = 2.30-7.00i
first x = -1.96+0.51i, second x = 0.42+0.04i
the only x = 1.70-3.70i
the only x = 3.70-3.10i
first x = -0.59+0.42i, second x = -0.16+1.82i
first x = -0.15+0.44i, second x = -0.15-0.55i
```
