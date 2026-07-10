# c652. 四、帶修改區間和(MRSQ)

## 內容

給你一段$\color{black}{\space N \space}$個正整數的序列$\color{black}{\space a_1\thicksim a_N \space}$，請你執行$\color{black}{\space Q \space}$筆操作。

## 輸入說明

第一行有兩個正整數$\color{black}{\space N,Q \space}$。


第二行有$\color{black}{\space N \space}$個正整數$\color{black}{\space a_i \space}$。


接下來有$\color{black}{\space Q \space}$行，每行代表一個操作。


如果是$\color{black}{\space 0 \space l \space r \space}$，代表詢問$\color{black}{\space [l,r] \space}$區間的和。


如果是$\color{black}{\space 1 \space l \space r \space}$，代表將$\color{black}{\space [l,r] \space}$區間的每個數字$\color{black}{\space a_i \space}$置換成$\color{black}{\space \lfloor \sqrt{a_i} \rfloor \space}$。

## 輸出說明

對於每個詢問，輸出詢問區間的和。

## 範例輸入 #1

```
5 3
16 9 1 5 3
0 1 5
1 1 5
0 1 5
```

## 範例輸出 #1

```
34
11
```
