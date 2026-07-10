# d691. 00496 - Simply Subsets

## 內容

在數學的定義中，一個集合裡有 0 或多個元素。
 在本問題中要請你判斷 2 個集合的關係。

## 輸入說明

輸入包含很多組測試資料，每組測試資料有 2 列。
 第一列代表第一個集合 A，第二列代表第二個集合 B。
 每個集合至多 100 個數字，數字間以一個空格分開。

## 輸出說明

對每筆輸入資料你應該要輸出以下其中一種情況：
- 
A is a proper subset of B （A 是 B 的子集合）

- 
B is a proper subset of A （B 是 A 的子集合）

- 
A equals B （A、B 是相同集合）

- 
A and B are disjoint （A、B 完全沒有交集）

- 
I'm confused! （A、B 有部分交集）

## 範例輸入 #1

```
55 27
55 27
9 24 1995
9 24
1 2 3
1 2 3 4
1 2 3
4 5 6
1 2
2 3
```

## 範例輸出 #1

```
A equals B
B is a proper subset of A
A is a proper subset of B
A and B are disjoint
I'm confused!
```
