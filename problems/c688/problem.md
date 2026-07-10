# c688. 數一數二

## 內容

$\color{black}{\text{定義 }b(n)\text{ 為 }n\text{ 以二進位表示時1的個數，}f_{i}(m)\text{ 為 }\{n | m \le n \le 2m-1, b(n)=i\}\text{ 的元素個數，請回答以下問題。}}$


$\color{black}{\text{1. 對於 }i\text{ 和 }r\text{，請求出 }f_{i}(2^r)\text{ 和 }f_{i}(2^r+1)\text{。}(i, r \le 60)}$


$\color{black}{\text{2. 給定 }i, m\text{ 和 }f_{i}(m)\text{，請求出 }f_{i}(m+1)\text{。}(i, m, f_{i}(m) \le 10^{18})}$


$\color{black}{\text{3. 對於 }m\text{，請求出 }f_{2}(m)\text{。}(m \le 10^{18})}$


$\color{black}{\text{4. 對於 }i\text{ 和 }r\text{，試決定最小的 }m_r\text{ 及最大的 }m'_r\text{ 使得 } f_{i}(m_r)=f_{i}(2^r)=f_{i}(m'_r)\text{。}(2 \le i \le 60, r \le 60)}$


$\color{black}{\text{5. 對於 }i\text{ 和 }m\text{，請求出 }f_{i}(m)\text{。}(i, m \le 10^{18})}$


$\color{black}{\text{(}i, r, m, m_r, m'_r \text{ 皆為非負整數。)}}$

## 輸入說明

第一行有兩個正整數 $\color{black}{Q, T}$，代表問的是第 $\color{black}{Q}$ 個問題且有 $\color{black}{T}$ 筆詢問。


接下來 $\color{black}{T}$ 行分別有若干以空格分開的數字，範圍和意義如題敘所述。

## 輸出說明

依序輸出每次詢問的答案。

## 範例輸入 #1

```
範例輸入一：
1 3
1 0
1 1
1 2

範例輸入二：
2 3
3 2017 55
3 2018 55
3 2019 55

範例輸入三：
3 4
2
20
201
2018

範例輸入四：
4 3
3 2
3 3
3 4

範例輸入五：
5 3
4 2018
5 2018
6 2018
```

## 範例輸出 #1

```
範例輸出一：
1 1
1 1
1 1

範例輸出二：
55
55
55

範例輸出三：
1
5
8
11

範例輸出四：
4 5
7 9
13 17

範例輸出五：
165
330
462
```
