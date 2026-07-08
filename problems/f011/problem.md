# f011. 巴尾萊鳥

## 內容

科學家在太平洋上接近赤道的一個小島，巴尾萊島(Bearla Island)，發現了一種鳥，巴尾萊鳥(Bearla Bird)
![image](ShowImage?id=1529)


科學家觀察到此種鳥類的器官裡有磁性物質，會與地球的磁場連結，使鳥類按照一種路線飛行


這個路線是一個 $\color{black}{n}\ $ 次方程式，$\color{black}{y = c_1x^n + c_2x^{n-1} +...+ c_{n-1}x^2 + c_nx + c_{n+1}}\ $，科學家稱之為磁力方程式( $\color{black}{c_k}\ $ 表係數)


鳥類只會在磁力方程式上飛行，但近年來地球暖化，氣候異常，使得地磁改變，科學家發現鳥類在磁力方程式的某一點上，如果地磁突然變動，鳥類就會沿著那一點的切線飛行，且之後也只能在切線上移動


科學家還發現鳥類在晚上會到赤道 $\color{black}{(y=0)}\ $ 休息


現在給你鳥類的磁力方程式、切線的切點 $\color{black}{P(a,b)}\ $，請問這一隻鳥晚上會在哪裡休息

## 輸入說明

第一行輸入 $\color{black}{T}\ $，代表有 $\color{black}{T}\ $ 筆測資


每筆測資第一行為 $\color{black}{n}\ $，代表磁力方程式是 $\color{black}{n}\ $ 次方程式


第二行為 $\color{black}{c_1\sim c_{n+1}}\ $


第三行為切點 $\color{black}{P(a,b)}\ $ 的$\color{black}{a}\ $


- $\color{black}{1≤T≤10^4}\ $
- $\color{black}{1≤n≤15}\ $
- $\color{black}{c_1≠0，c_k∈Z，|c_k|≤100}\ $
- $\color{black}{a∈Z，|a|≤100}\ $

## 輸出說明

如果鳥類無法休息，輸出 $\color{black}{It\ cannot\ sleep!}\ $


如果鳥類在哪裡都可以休息，輸出 $\color{black}{It\ can\ sleep\ everywhere!}\ $


否則輸出 $\color{black}{(s,0)}\ $，$\color{black}{s}\ $ 請四捨五入到小數第 $\color{black}{3}\ $ 位


$\color{black}{Ex：}\ $


- $\color{black}{12.3445→ 12.345，12.3444→ 12.344}\ $
$\color{black}{0.0005→ 0.001，0.0004→ 0.000}\ $
$\color{black}{-12.3445→ -12.345，-12.3444→ -12.344}\ $
$\color{black}{-0.0005→ -0.001，-0.0004→ 0.000}\ $

## 範例輸入 #1

```
5
2
1 1 1
0
2
1 1 1
1
2
1 0 0
0
3
1 0 -3 0
1
3
1 0 0 1
-1
```

## 範例輸出 #1

```
(-1.000,0)
(0.000,0)
It can sleep everywhere!
It cannot sleep!
(-1.000,0)
```
