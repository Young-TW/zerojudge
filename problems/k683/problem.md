# k683. A+B Problem - Revisited

## 內容

這是一個 output-only 問題。


• 題目 :  給你 $A, B$ 兩個非負整數，請你算出 $A+B$ 的值? 但是這次必須得使用下列的方式求得 : 


現在有個程式語言，他的程式語法如下，你可以呼叫下列的方法進行運算，這個程式語言有 $26$ 個變數 $A, B, C,... , Z$ 可供存取，一開始給定 $A, B$，剩下的 $C, D, E,... , Z$ 皆預設為 $0$，這些變數可存取 $0\sim 2^{64}-1 $ 範圍的值，超出範圍(overflow)會被模 $2^{64}$。請你利用這個程式語言的方式求出 $A+B$ 。


方法用途$\text{AND X Y}$將目前的 $X$ 做 $and\ Y$ 運算，也就是 $X\rightarrow X\ and\ Y$$\text{OR X Y}$將目前的 $X$ 做 $or \ Y$ 運算$\text{XOR X Y}$將目前的 $X$ 做 $xor\ Y$ 運算$\text{RS X Y}$將目前的 $X$ 進行右移運算 $Y$ 格$\text{LS X Y}$將目前的 $X$ 進行左移運算 $Y$ 格$\text{SET X Y}$將目前變數 $X$ 的值設定為 $Y$$\text{MUL X Y}$將目前變數 $X$ 的值設定為 $X\times Y$$\text{DIV X Y}$將目前變數 $X$ 的值設定為 $\lfloor{\frac{x}{y}}\rfloor$$\text{ANS Y}$回傳答案 $Y$，此指令執行完後程式中止
 


上述方法的 $X$ 是一個變數， $Y$ 可以是一個變數抑或著是一個非負整數 (需滿足$ 0 ≤ Y ≤ 2^{64}-1$)，注意 $\text{and or xor}$ 指的是位元運算。


請你利用上面的方法計算出 $A+B$ 並利用 $\text{ANS}$ 方法回傳答案，撰寫的方法請參考範例輸出。

## 輸入說明

本題為 output-only 問題，無任何輸入。

## 輸出說明

輸出你的解法，各方法中間需換行，最多可輸出$2\times 10^3$行，格式可以參考下面的輸出範例。

## 範例輸入 #1

```

```

## 範例輸出 #1

```
SET C A
MUL C B
LS C 1
OR C A
DIV C B
XOR C A
ANS C
```
