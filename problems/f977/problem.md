# f977. '97 Bonnie & Clyde

## 內容

![image](ShowImage?id=1791)


"Sit back in your chair honey, quit tryin' to climb out (wa'!)
I told you it's okay hai hai, want to ba-ba?
Take a night-night? nan-a-boo, goo-goo ga-ga?
Her make goo-goo ca-ca? da-da change your dia-dee.
Clean the baby up so her can take a nighty-nighty.
Your dad'll wake her up as soon as we get to the water.
Ninety-seven bonnie and clyde, me and my daughter."


Marshall 和 Hailie 一起去湖邊玩，兩個人一起往湖裡丟東西


東西在沉入水中時只受到三個力，重力、浮力和水的阻力


假設重力和浮力造成的向下加速度固定是 $\color{black}{A\ }$


水的阻力造成的向上加速度為 $\color{black}{kv^2}\ $ ( $\color{black}{v}\ $ 代表當前速度 )


那總體來說的向下加速度就是 $\color{black}{A - kv^2}\ $


請你求出在初速為 $\color{black}{0}\ $ 的狀況下，過了 $\color{black}{t}\ $ 單位時間，這個物體的位移、速度和加速度


(假設都沒碰到湖底)

## 輸入說明

輸入有多行


每行有正整數 $\color{black}{A, k, t}\ $


- $\color{black}{1≤ A,k ≤1000}\ $
- $\color{black}{1≤ t ≤ 10^7}\ $

## 輸出說明

輸出三行


第一行輸出 $\color{black}{x(t)=...}\ $


第二行輸出 $\color{black}{v(t)=...}\ $


第三行輸出 $\color{black}{a(t)=...}\ $


四捨五入到小數第 $\color{black}{2}\ $ 位

## 範例輸入 #1

```
1 2 8
1 1 1
2 6 4
```

## 範例輸出 #1

```
x(8)=5.31
v(8)=0.71
a(8)=0.00
x(1)=0.43
v(1)=0.76
a(1)=0.42
x(4)=2.19
v(4)=0.58
a(4)=0.00
```
