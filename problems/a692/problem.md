# a692. 蘿莉區域劃分

## 內容

天又酷國有 $\color{black}{n}$ 座城市，這些城市以 $\color{black}{n-1}$ 條道路相連，且彼此可透過這些道路互相到達。天又酷國國王是個蘿莉控，經過調查，他知道每個城市的蘿莉數。他現在要把他的國家分成 $\color{black}{k}$ 個區域，滿足「任一區域內的任兩座城市之間，往來不需經過該區域外的城市」。假設劃分後，各個區域內的蘿莉數為 $\color{black}{a_1, a_2, \ldots, a_k}$，他希望 $\color{black}{\min\{a_i: 1 \leq i \leq k\}}$ 的值越大越好。請問在所有的劃分方法中， $\color{black}{\min\{a_i: 1 \leq i \leq k\}}$ 的最大值為何？

## 輸入說明

第一行有兩個數字 $\color{black}{n, k}$，代表天又酷國的城市數目和天又酷國國王想劃分出的區域數。
第二行有 $\color{black}{n}$ 個正整數 $\color{black}{l_1, l_2, \ldots, l_n}$，代表各個城市的蘿莉數。
接下來的 $\color{black}{n-1}$ 行，每行有兩個正整數 $\color{black}{u, v}$，代表有一條道路連接城市 $\color{black}{u}$ 和城市 $\color{black}{v}$。


- $\color{black}{1 \leq k \leq n \leq 10^6}$
- $\color{black}{1 \leq l_i \leq 10^8}$

## 輸出說明

請輸出在所有劃分方法中，$\color{black}{\min\{a_i: 1 \leq i \leq k\}}$ 的最大值。

## 範例輸入 #1

```
12 3
10 9 1 3 9 9 1 4 6 1 2 3
1 2
2 4
2 5
2 6
4 9
1 3
3 7
3 8
8 10
8 11
8 12
```

## 範例輸出 #1

```
10
```
