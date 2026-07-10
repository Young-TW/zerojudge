# c203. 13185 - DPA Numbers I

## 內容

一個整數b如果可以被另一個整數a整除（在這裡a>b），我們稱b是a的一個因數。


Perfect Number是一個正整數並且等於其所有因數（不包含它自己）的和。


例如：6和28都是perfect number。因為6=1+2+3，28=1+2+4+7+14。


如果一個正整數不是perfect，那他就是deficient或者是 abundant，根據其所有因數的和是小於或大於這個數本身。因此，9是deficient因為1+3<9。而12是abundant因為1+2 +3+4+6>12。



請寫一個程式求出某一個數是perfect, deficient 或者abundant。

## 輸入說明

輸入的第一列有一個正整數t代表以下有幾筆測資。（ 1 <= t <= 500 ）


每筆測資一列，有一個正整數 n（2 <= n <= 1000 ）

## 輸出說明

對每筆測資輸出一列，輸出 n 是perfect, deficient 或者abundant

## 範例輸入 #1

```
10
5
6
16
18
21
28
29
30
40
43
```

## 範例輸出 #1

```
deficient
perfect
deficient
abundant
deficient
perfect
deficient
abundant
abundant
deficient
```
