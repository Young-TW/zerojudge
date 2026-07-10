# h386. Apples and Bananas

## 內容

你有n個蘋果和m個香蕉，他們的重量介於1到k之間，今天請你計算對於每個介於2~2k之間的重量w，有幾種方式可以挑選一個蘋果和香蕉，使他們重量總重為w。


There are apples and bananas and each of them has an integer weight between 1..k. Your task is to calculate for each weight w between 2...2k the number of ways we can choose an apple and a banana whose combined weight is w.


限制:


1 ≤ k,n,m ≤ 2*105


1 ≤ ai, bi ≤ k

## 輸入說明

第一行輸入三個整數k、n、m，分別代表重量範圍、蘋果數量、香蕉數量。


第二行輸入n個整數，代表蘋果各自重量。


最後一行輸入m個整數，代表香蕉各自重量。


The first input line contains three integers k, n and m: the number k, the number of apples and the number of bananas.

The next line contains n integers a1,a2,...,an :weight of each apple.

The last line contains m integers b1,b2,...,bn  :weight of each banana.

## 輸出說明

輸出一行，對於每個介於2到2k之間的重量w，輸出有幾種方式可以選擇一個蘋果和一個香蕉，使得總重為w，數字與數字中間以空白隔開。


For each integer w between 2…2k print the number of ways to choose an apple and a banana whose combined weight is w.

## 範例輸入 #1

```
5 3 4
5 2 5
4 3 2 3
```

## 範例輸出 #1

```
0 0 1 2 1 2 4 2 0
```
