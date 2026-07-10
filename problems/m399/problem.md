# m399. print(max(A,B))

## 內容

這是一個 output-only 問題。


• 題目 :  給你 $A, B$ 兩個非負整數，請你求出 $max(A, B)$ 的值? 也就是輸出 $A, B$ 之中比較大的那個值，但是這次必須得使用下列的方式求得 : 


現在有個程式語言，他的程式語法如下，你可以呼叫下列的方法進行運算，這個程式語言有 $26$ 個變數 $A, B, C,... , Z$ 可供存取，一開始給定 $A, B$，剩下的 $C, D, E,... , Z$ 皆預設為 $0$，這些變數可存取 $0\sim 2^{64}-1 $ 範圍的值 (即 C++ 的 unsigned long long int) ，超出範圍(overflow)會被模 $2^{64}$ 。請你利用這個程式語言的方式求出 $max(A, B)$ 。


方法用途$\text{AND X Y Z}$將目前的 $X$ 設定為「$Y\ \text{AND}\ Z$」$\text{OR X Y Z}$將目前的 $X$ 設定為「$Y\ \text{OR}\ Z$」$\text{XOR X Y Z} $將目前的 $X$ 設定為「$Y\ \text{XOR}\ Z$」$\text{RS X Y Z}$將目前的 $X$ 設定為「進行右移運算 $Z$ 格的 $Y$」$\text{LS X Y Z}$將目前的 $X$ 設定為「進行左移運算 $Z$ 格的 $Y$」
$\text{ADD X Y Z}$



將目前變數 $X$ 的值設定為「$Y + Z$」



$\text{SUB X Y Z}$



將目前變數 $X$ 的值設定為「$Y - Z$」，如果 $Y - Z < 0$ 則  $X \rightarrow (Y - Z + 2^{64})$



$\text{MUL X Y Z}$



將目前變數 $X$ 的值設定為「$Y\times Z$」


$\text{DIV X Y Z}$
將目前變數 $X$ 的值設定為「$\lfloor{\frac{Y}{Z}}\rfloor$」


$\text{SET X Y}$將目前變數 $X$ 的值設定為 $Y$$\text{ANS X}$回傳答案 $X$，此指令執行完後程式中止
 


呼叫上述方法時，輸入的 $X$ 是一個變數名稱， $Y$, $Z$ 可以是一個變數名稱抑或著是一個非負整數的常數 (需滿足$ 0 ≤ Y, Z ≤ 2^{64}-1$)，注意 $\text{AND, OR, XOR}$ 以及左移、右移運算指的都是位元運算。


請你利用上面的方法計算出 $max(A, B)$ 並利用 $\text{ANS}$ 方法回傳答案，撰寫的方法請參考範例輸出。

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
MUL C B C
LS C 1
OR D A C
DIV E C D
SUB F E A
ADD G F D
SUB H G B
ANS H
```
