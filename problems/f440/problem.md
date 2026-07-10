# f440. 10130 - SuperSale

## 內容

有間商店共有N種商品每種商品有不同的重量和價值且每人每種最多只能拿一個
求出G個人最大能拿走多少價值的商品


There is a SuperSale in a SuperHiperMarket. Every person can take only one object of each kind, i.e.one TV, one carrot, but for extra low price. We are going with a whole family to that SuperHiperMarket. Every person can take as many objects, as he/she can carry out from the SuperSale. We have given list of objects with prices and their weight. We also know, what is the maximum weight that every person can stand. What is the maximal value of objects we can buy at SuperSale?

## 輸入說明

第一行有個T代表測資數目(1 ≤ T ≤ 1000)
每筆次測資第一行有個數字N代表商品數目(1 ≤ N ≤ 1000)
接下來N行有P,W分別代表商品的價值和重量
之後有一行G代表有G個人(1 ≤ G ≤ 100)
接下來G行有每個人的負重(皆小於等於30)


The input consists of T test cases. The number of them (1 ≤ T ≤ 1000) is given on the first line of the input file. Each test case begins with a line containing a single integer number N that indicates the number of objects (1 ≤ N ≤ 1000). Then follows N lines, each containing two integers: P and W.The first integer (1 ≤ P ≤ 100) corresponds to the price of object. The second integer (1 ≤ W ≤ 30)corresponds to the weight of object. Next line contains one integer (1 ≤ G ≤ 100) its the number of people in our group. Next G lines contains maximal weight (1 ≤ MW ≤ 30) that can stand this i-th person from our family (1 ≤ i ≤ G).

## 輸出說明

輸出最大能拿走多少價值的商品
For every test case your program has to determine one integer. Print out the maximal value of goods which we can buy with that family.

## 範例輸入 #1

```
2
3
72 17
44 23
31 24
1
26
6
64 26
85 22
52 4
99 18
39 13
54 9
4
23
20
20
26
```

## 範例輸出 #1

```
72
514
```
