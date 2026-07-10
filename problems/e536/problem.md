# e536. 10487 - Closest Sums

## 內容

給定一組整數集合，然後是一系列查詢。
每個查詢會為您提供一個數字，並要求從集合中找出兩個最接近查詢數字的數字之和。

## 輸入說明

輸入包含多組測資。
測資第一行有一個整數n (1 < n ≤ 1000)，代表整數集合中有多少個數字。
n = 0代表輸入結束。
接下來的n行包含n個數字，每行一個。
接下來一行包含給出查詢數量的正整數m (0 < m < 25)。
接下來的m行包含查詢整數，每行一個。

## 輸出說明

對於每組測資，輸出測資編號。
對於每個查詢輸出兩個最接近查詢數字的數字之和。
格式請參考範例輸出。

## 範例輸入 #1

```
5
3
12
17
33
34
3
1
51
30
3
1
2
3
3
1
2
3
3
1
2
3
3
4
5
6
0
```

## 範例輸出 #1

```
Case 1:
Closest sum to 1 is 15.
Closest sum to 51 is 51.
Closest sum to 30 is 29.
Case 2:
Closest sum to 1 is 3.
Closest sum to 2 is 3.
Closest sum to 3 is 3.
Case 3:
Closest sum to 4 is 4.
Closest sum to 5 is 5.
Closest sum to 6 is 5.
```
