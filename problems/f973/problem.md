# f973. /╲/\(•̀w•́)/\╱\

## 內容

在解這個題目之前，大家請先認識 Bully Maguire，他是在 Tobey Maguire 版蜘蛛人電影裡被猛毒 (Venom) 入侵身體後的蜘蛛人，因為被附身，所以變得酷酷壞壞的。


網友常常把其他電影的人物換成 Bully Maguire 的臉，像是酷寒戰士、星際大戰、終局之戰等等。


Bully Maguire 很會跳舞，大家過去幾年都一致認為他是最會跳舞的人，但是最近有一個挑戰者出現了，那就是 Zemo，Zemo 除了做反派之外，也很會跳舞。


於是他們決定要 battle！！！



![image](ShowImage?id=1805)


但是他們要找出一個評分標準，於是他們隨便找了一個長這樣的函數 $\color{black}{f(x)}\ $，兩個人各選一個數字 $\color{black}{x_1, x_2}\ $。


$\color{black}{f(x)=\sum\limits_{n=0}^∞a^ncos(b^nπx)}\ $


如果 $\color{black}{f(x_1), f(x_2)}\ $ 差距小於 $\color{black}{1}\ $，兩人勢均力敵，就算平手。


否則如果 $\color{black}{f(x_1)}\ $ 大，Bully Maguire 就贏了。


否則如果 $\color{black}{f(x_2)}\ $ 大，Zemo 就贏了。


不過為了檢察有無作弊，贏家要說出他那一點的切線斜率 (四捨五入到小數第 $\color{black}{2}\ $ 位)，平手的話就不用。

## 輸入說明

多筆輸入


每筆第一行輸入 $\color{black}{a,b}\ $ ( $\color{black}{a}\ $ 為 $\color{black}{2}\ $ 位小數，$\color{black}{b}\ $ 為正奇數 )


第二行輸入 $\color{black}{x_1, x_2}\ $ ( $\color{black}{x_1,x_2}\ $ 為 $\color{black}{1}\ $ 位小數)


- $\color{black}{0<a<0.1，ab≥6}\ $
- $\color{black}{-100≤ x_1,x_2 ≤ 100}\ $

## 輸出說明

如果平手 (差距小於 $\color{black}{1}\ $ )，輸出 $\color{black}{Tie}\ $


否則如果 $\color{black}{f(x_1)}\ $ 大，輸出 $\color{black}{Bully\ Maguire\ Wins}\ $


否則如果 $\color{black}{f(x_2)}\ $ 大，輸出 $\color{black}{Zemo\ Wins}\ $


若可分出勝負，下一行接者輸出贏家切線的斜率，四捨五入到小數第 $\color{black}{2}\ $ 位 ( 若恰無斜率則輸出 $\color{black}{nan}\ $ )


$\color{black}{Ex：}\ $


- $\color{black}{12.345→ 12.35，12.344→ 12.34}\ $
$\color{black}{0.005→ 0.01，0.004→ 0.00}\ $
$\color{black}{-12.345→ -12.35，-12.344→ -12.34}\ $
$\color{black}{-0.005→ -0.01，-0.004→ 0.00}\ $

## 範例輸入 #1

```
0.01 601
0.0 1.0
0.01 601
-1.0 1.0
```

## 範例輸出 #1

```
Bully Maguire Wins
nan
Tie
```
