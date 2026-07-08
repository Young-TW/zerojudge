# e509. Conscription

## 內容

Windy has a country, and he wants to build an army to protect his country. He has picked up N girls and M boys and wants to collect them to be his soldiers. To collect a soldier without any privilege, he must pay 10000 $. There are some relationships between girls and boys and Windy can use these relationships to reduce his cost. If girl x and boy y have a relationship d and one of them has been collected, Windy can collect the other one with 10000-d $. Now given all the relationships between girls and boys, your assignment is to find the least amount of money Windy has to pay. Notice that only one relationship can be used when collecting one soldier.


Windy 要建立一支軍隊，他選了 N 個女孩與 M 個男孩。每招募一個「人」就要付出 10,000 人民幣。但在這些男孩女孩中，某些男孩與女孩存在著愛戀，並有個愛戀值 d。當招募的男孩與女孩有戀愛關係時，其中一個人的費用就可以降低為 10,000 - d。現在給出這些關係，求出 Windy 最少可以用多少錢招募這些男孩與女孩。要注意的是，每一個「人」都僅可以使用一條關係。

## 輸入說明

The first line of input is the number of test case.
The first line of each test case contains three integers, N, M and R.
Then R lines followed, each contains three integers xi, yi and di.


測試資料開頭由一個整數 K 開始，表示接下來有 K 組測試資料。


每一組測試資料由三個整數開始 N M R，表示 Windy 要招募 N 個女孩與 M 個男孩，且這些男孩女孩中存在著 R 對關係。接著有 R 行，每行三個整數 xi yi di，表示女孩 xi 與男孩 yi 有存在著愛戀，且其愛戀值為 di。


 


1 ≤ N, M ≤ 10000
0 ≤ R ≤ 50,000
0 ≤ xi < N
0 ≤ yi < M
0 < di < 10000

## 輸出說明

For each test case output the answer in a single line.


對於每一筆測試資料，輸出一個整數，表示最少 Windy 最少付出多少費用可以招募到他所需要的士兵。

## 範例輸入 #1

```
2
5 5 8
4 3 6831
1 3 4583
0 0 6592
0 1 3063
3 3 4975
1 3 2049
4 2 2104
2 2 781
5 5 10
2 4 9820
3 2 6236
3 1 8864
2 4 8326
2 0 5156
2 0 1463
4 1 2439
0 4 4373
3 4 8889
2 4 3133
```

## 範例輸出 #1

```
71071
54223
```
