# g200. lvpb 的族譜

## 內容

這裡有一疊排好出生序的族譜資料, 請整理好後, 依題目的要求輸出第 k 代的所有人名。


輸出時請依分支序, 年齡排序後輸出。

## 輸入說明

單筆測資, 測資的第一列為 root n m


root 為祖先的名字, n 表示總共有幾名子孫, m 表示有幾筆詢問。


第 2 列開始有 n 列, 每一列有 2 個字串, a b 表示 a 生 b, 年齡為出生序遞減。


最後有 m 列詢問, 每個詢問有一個數字 k


k 表示請你排序輸出第 k 代子孫的姓名。


排序方式：請依分支序, 年齡由小而大, 排序後輸出。

## 範例輸入 #1

```
lvpb 9 6
lvpb ndml
ndml uods
uods ytaq
lvpb bpet
ytaq gdpq
ndml dswt
ytaq yzoa
uods pmhu
gdpq pcbj
1
3
6
5
4
2
```

## 範例輸出 #1

```
lvpb
uods dswt
pcbj
gdpq yzoa
ytaq pmhu
ndml bpet
```

## 範例輸入 #2

```
a 12 4
a b
a c
c d
c e
a f
b g
f h
b i
f j
e k
d l
g m
1
2
3
4
```

## 範例輸出 #2

```
a
b c f
g i d e h j
m l k
```
