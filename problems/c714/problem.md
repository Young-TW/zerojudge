# c714. 壞掉的二元搜尋樹

## 內容

$\color{black}{\space oT \space}$不小心把一棵原本是正常的二元搜尋樹打亂了，他甚至還在不知情的情況下將其組裝了起來，導致現在不能把他重新排列。


　　為了在遭限制的條件下修復好這棵二元搜尋樹，只好退一步直接修改節點上的值，不過即使如此，每個節點能修改成的值也必須是整數，且都帶有修改的代價。


　　現在告訴你這棵二元樹的長相、節點上的值和修改代價，請問你最少要花費多少代價才能將其修改成一棵正常的二元搜尋樹呢？


　　因為$\color{black}{\space oToT \space}$的關係，對$\color{black}{\space oT \space}$來說一棵正常的二元搜尋樹是不可以有兩個值相同的，即使是修改後也一樣，所以切記不要讓兩個不同的節點有相同的值(修改的途中相同沒問題)。

## 輸入說明

首行一個正整數$\color{black}{\space T(1\leq T\leq 20) \space}$，代表測資筆數。


每筆測資有四行，第一行一個正整數$\color{black}{\space N(1\leq N\leq 5\times 10^4) \space}$，代表節點數量；


第二行有一個長度$\color{black}{\space 2N \space}$的序列$\color{black}{\space l_1,r_1,l_2,r_2,...,l_N,r_N(0\leq l_i,r_i \leq N)\space}$，代表編號$\color{black}{\space i \space}$節點的被打亂後的左右子節點編號(保證編號$\color{black}{\space 1 \space}$的節點為根節點，如果$\color{black}{\space l_i=0 \space}$或$\color{black}{\space r_i=0 \space}$，表示該節點沒有左或右子節點)；


第三行有一個序列$\color{black}{\space v_1\sim v_N (1\leq v_i\leq N) \space}$，代表編號$\color{black}{\space i \space}$節點的值；


第四行有有一個序列$\color{black}{\space w_1\sim w_N (1\leq w_i\leq 10^9) \space}$，代表修改編號$\color{black}{\space i \space}$節點值的代價。

## 輸出說明

請輸出$\color{black}{\space T \space}$行，每行代表該筆測資滿足目標的最小花費。

## 範例輸入 #1

```
2
5
2 3 0 0 4 5 0 0 0 0
3 1 4 5 2
1 5 6 2 3
5
0 2 0 3 0 4 0 5 0 0
1 2 4 3 5
100 100 1 1 100
```

## 範例輸出 #1

```
6
2
```
