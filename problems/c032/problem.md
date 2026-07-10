# c032. 00382 - Perfection

## 內容

一個整數b如果可以被另一個整數a整除（在這裡a>b），我們稱b是a的一個因數。

Perfect Number是一個正整數並且等於其所有因數的和。

例如：6和28都是perfect number。因為6=1+2+3，28=1+2+4+7+14。

如果一個正整數不是perfect，那他就是deficient或者是 abundant，根據其所有因數的和是小於或大於這個數本身。因此，9是deficient因為1+3<9。而12是abundant因為1+2 +3+4+6>12。
 請寫一個程式求出某一個數是perfect, deficient 或者abundant。

## 輸入說明

有一連串（不會超過100個）的正整數n（1 <= n < 60000）,n=0代表輸入結束。

## 輸出說明

請參考 Sample Output。 數字部分佔5個字元長度，靠右對齊。與後方的敘述間空2個空白格。

## 範例輸入 #1

```
15 28 6 56 60000 22 496 0
```

## 範例輸出 #1

```
PERFECTION OUTPUT
   15  DEFICIENT
   28  PERFECT
    6  PERFECT
   56  ABUNDANT
60000  ABUNDANT
   22  DEFICIENT
  496  PERFECT
END OF OUTPUT
```
