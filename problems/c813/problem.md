# c813. 11332 - Summing Digits

## 內容

對於所有正整數$\color{black}{\space n\space}$，我們定義一函數$\color{black}{\space f(n)\space}$為$\color{black}{\space n\space}$ 的每一個十進位數字的總和，若再把$\color{black}{\space f(n)\space}$代入函數中可得最到$\color{black}{\space n,f(n),f(f(n)),f(f(f(n))) \dots\space}$最後得到僅有一位數字的值，並定義該值為$\color{black}{\space g(n)\space}$。


例如，當 $\color{black}{\space n=1234567892\space}$，則：


$\color{black}{\space f(n)=1+2+3+4+5+6+7+8+9+2=47\space}$
$\color{black}{\space f(f(n))=4+7=11\space}$
$\color{black}{\space f(f(f(n)))=1+1=2\space}$


所以，$\color{black}{\space g(1234567892)=2\space}$。

## 輸入說明

輸入的每一行會有一個正整數$\color{black}{\space n\space}$，其值最大到$\color{black}{\space 2\times 10^9\space}$，你必須輸出$\color{black}{\space g(n)\space}$。輸入是以$\color{black}{\space 0\space}$值做為結束，該值不需要輸出。

## 輸出說明

如輸入所述。

## 範例輸入 #1

```
2
11
47
1234567892
0
```

## 範例輸出 #1

```
2
2
2
2
```
