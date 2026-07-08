# f026. 吃外賣遊戲

## 內容

小爆點了 $\color{black}{n}\ $ 份外賣，編號為 $\color{black}{1\sim n}\ $。第 $\color{black}{i}\ $ 份外賣有豐富度 $\color{black}{a_i}\ $、飽足度 $\color{black}{b_i}\ $，小爆吃完這份外賣的飽足感會是 $\color{black}{a_i^{b_i}}\ $。


現在有一種操作：選擇兩份不同的外賣，編號為 $\color{black}{i,j}\ $，可選擇一個非負實數 $\color{black}{r}\ $，使 $\color{black}{a_i}\ $ 減去 $\color{black}{r}\ $，$\color{black}{a_j}\ $ 加上 $\color{black}{r}\ $，也就是把編號 $\color{black}{i}\ $ 的豐富度移一些到編號 $\color{black}{j}\ $。但是要注意，在過程中不可使任何一份外賣的豐富度小於 $\color{black}{0}\ $。


假設小爆可以做任意次上述操作，現在他想要讓每份外賣的飽足感相乘最大，也就是使 $\color{black}{\prod_{i=1}^{n} a_i^{b_i}}\ $ 最大。請你回答在經過操作後，飽足感乘積最大可以是多少？

## 輸入說明

第一行有 $\color{black}{t}\ $，代表測資筆數。


每筆測資第一行有 $\color{black}{n}\ $，代表小爆點了 $\color{black}{n}\ $ 份外賣。


第二行有 $\color{black}{n}\ $ 個 $\color{black}{1}\ $ 位小數 $\color{black}{a_1\sim a_n}\ $，代表每份外賣的豐富度。


第三行有 $\color{black}{n}\ $ 個正整數 $\color{black}{b_1\sim b_n}\ $，代表每份外賣的飽足度。


- $\color{black}{1≤t≤10^3}\ $
- $\color{black}{1≤n≤10^3}\ $
- $\color{black}{0≤a_i≤10^3}\ $
- $\color{black}{1≤b_i≤100}\ $
- $\color{black}{\sum_{i=1}^{n}a_i>0}\ $

## 輸出說明

使用科學記號形式輸出答案，格式為 $\color{black}{x\ E\ y}\ $。


$\color{black}{1≤x<10}\ $，$\color{black}{x}\ $ 請四捨五入到小數第三位。$\color{black}{y}\ $ 為一整數。

## 範例輸入 #1

```
2
1
5.0
3
2
2.0 4.0
1 1
```

## 範例輸出 #1

```
1.250E2
9.000E0
```
