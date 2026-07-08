# f996. N項的費氏數列 - Extreme

## 內容

![image](ShowImage?id=2022)


原題


Leonardo Pisano Bigollo 1175~1250


Waimai：「這位是費波那契，是西方第一個研究費波那契數列的人，因為他的研究，所以費波那契數列以費波那契數列命名。」


Caido：「你是說第一項和第二項是 $\color{black}{1}\ $，第 $\color{black}{k}\ $ 項是第 $\color{black}{k - 1}\ $ 項加第 $\color{black}{k - 2}\ $ 項的數列嗎?」


Waimai：「對，不過我們現在要把 $\color{black}{2}\ $ 項的費式數列變成 $\color{black}{n}\ $ 項的費氏數列，數列的前 $\color{black}{n}\ $ 項是 $\color{black}{1}\ $，第 $\color{black}{k}\ $ 項是第 $\color{black}{k - n}\ $ 項到第 $\color{black}{k - 1}\ $ 項的總和。即 $\color{black}{f_n(1)\sim f_n(n) = 1，f_n(k) = \sum_{i = k-n}^{k-1}f_n(i)\ (k>n)}\ $。」


Caido：「聽起來滿簡單的啊。」


Waimai：「嗯，不過因為數字可能會很大，所以答案要 $\color{black}{mod\ 10^9+7}\ $ 後再輸出。」

## 輸入說明

第一行有一個整數 $\color{black}{t}\ $，代表測資筆數。


接下來 $\color{black}{t}\ $ 行每行有兩個數字 $\color{black}{n, k}\ $，代表要求 $\color{black}{f_n(k)}\ $。


- $\color{black}{1≤t≤10^5}\ $
- $\color{black}{2≤n≤15}\ $
- $\color{black}{1≤k≤2^{60}}\ $

## 輸出說明

請把答案 $\color{black}{mod\ 10^9+7}\ $ 再輸出

## 範例輸入 #1

```
5
2 5
3 2
10 12
12 1000
15 1125899906842624
```

## 範例輸出 #1

```
5
1
19
282446896
121395600
```
