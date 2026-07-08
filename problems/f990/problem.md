# f990. 距離

## 內容

有一天小 C 正在算數學，遇到一個題目：有兩個點 $\color{black}{(0,1)}\ $ 和 $\color{black}{(2,3)}\ $，要在 $\color{black}{x}\ $ 軸上取一個點，要取哪一點到兩個點的距離和會最小呢？


正當小 C 想不出來時，小 B 告訴他了解法，原來只要把 $\color{black}{(2,3)}\ $ 對稱到 $\color{black}{(2,-3)}\ $，再把 $\color{black}{(0,1)}\ $ 跟 $\color{black}{(2,-3)}\ $ 連線，跟 $\color{black}{x}\ $ 軸的交點就是答案了，所以答案是 $\color{black}{(0.5,0)}\ $。


小 C 又問了下一題，有 $\color{black}{n}\ $ 個點在平面上，有一條直線 $\color{black}{y = mx + k}\ $，要在這條線上取一點，而且這點到其他 $\color{black}{n}\ $ 個點的距離和最小，請問這點的 $\color{black}{x}\ $ 座標值？


這就難倒小 B 了，於是他請求你的幫助。

## 輸入說明

第一行有一個數字 $\color{black}{t}\ $，代表有幾組測試資料。


每組測試資料第一行有三個整數 $\color{black}{n,m,k}\ $，代表平面上有 $\color{black}{n}\ $ 個點，和直線為 $\color{black}{y = mx + k}\ $。


接下來 $\color{black}{n}\ $ 行，每行有兩個整數 $\color{black}{x_i, y_i}\ $，代表 $\color{black}{n}\ $ 個點的座標值。


- $\color{black}{1≤t≤10}\ $
- $\color{black}{1≤n≤10^5}\ $
- $\color{black}{\lvert m,k,x_i,y_i\rvert≤10^6}\ $

## 輸出說明

每筆測試資料輸出 $\color{black}{x_{ans}}\ $，代表答案的 $\color{black}{x}\ $ 座標。


令 $\color{black}{f(x)}\ $ 代表用這個 $\color{black}{x}\ $ 值代入，與 $\color{black}{n}\ $ 個點的距離和。


只要用 $\color{black}{x_{ans}}\ $ 算出的 $\color{black}{f(x_{ans})}\ $ 與標準輸出檔裡的 $\color{black}{x_{ac}}\ $ 算出的 $\color{black}{f(x_{ac})}\ $，滿足 $\color{black}{\lvert f(x_{ac})-f(x_{ans}) \rvert ≤ 1}\ $，就算通過。


格式不限，只要可以正常運作就好了。

## 範例輸入 #1

```
1
2 0 0
0 1
2 3
```

## 範例輸出 #1

```
0.499991234567
```
