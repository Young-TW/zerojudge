# i177. 小畫家 (Painter)

## 內容

給定一張高度為 $\color{black}{H}$ 像素、寬度為 $\color{black}{W}$ 像素的點陣圖 $\color{black}{P}$，由上至下數來第 $\color{black}{i}$ 個、由左至右數來第 $\color{black}{j}$ 個的像素以 $\color{black}{(i, j)}$ 表示。$\color{black}{(i, j)}$ 的色彩編號為 $\color{black}{C_{ij}}$。


小明用某繪圖軟體開啟點陣圖 $\color{black}{P}$，使用軟體中的「填入色彩」功能：用滑鼠點擊 $\color{black}{S_i,S_j}$，所有與 $\color{black}{S_i,S_j}$ 屬於同一個「連通區塊」像素的色彩編號均會轉換成指定的色彩$\color{black}{Z}$。對於影像$\color{black}{P}$ 上任兩個上、下、左或右相鄰的像素$\color{black}{(i, j)}$  與$\color{black}{(i', j')}$ (即 $\color{black}{(i', j') ∈{(i-1, j ), (i+1, j ), (i, j-1), (i, j+1)}} )$，如果$\color{black}{C _{ij}}$ 和 $\color{black}{C_{i'j'}}$ 相同，則說$\color{black}{(i, j)}$ 與$\color{black}{(i', j') }$ 同屬於同一個「連通區塊」。


例如有一張 $\color{black}{ H = 5 }$ 像素、$\color{black}{ W = 6 }$ 像素的原始點陣圖 $\color{black}{ P }$ 如圖一所示，用滑鼠點擊$\color{black}{(S_i, S_j) = (3, 2)}$，將所有與其屬於同一個「連通區塊」像素的色彩編號轉換成 $\color{black}{ Z = 4 }$。填入色彩之後的新點陣圖 $\color{black}{ P' }$ 如圖二所表示。



![image](ShowImage?id=2085)


請寫一個程式在給定原始點陣圖 $\color{black}{P}$ 的資訊的情形下，模擬「填入色彩」$\color{black}{Z}$ 之後的新點陣圖 $\color{black}{P'}$。

## 輸入說明

第一列有五個非負整數依序為 $\color{black}{H}$、$\color{black}{W}$、$\color{black}{S_i}$、$\color{black}{S_j}$ 與 $\color{black}{Z}$，表示原始點陣圖$\color{black}{P}$ 的高度為 $\color{black}{H}$ 像素、寬度為 $\color{black}{W}$ 像素、用滑數點擊$\color{black}{(S_i, S_j)}$、將該連通區塊的色彩改為色彩$\color{black}{Z}$。第 $\color{black}{2}$ 列到第 $\color{black}{H+1}$ 列代表原始點陣圖每個像素的原始顏色，每行都有 $\color{black}{W}$ 個非負整數，彼此以一個空白隔開；第 $\color{black}{i+1}$ 列的第 $\color{black}{j}$ 個數字表示 $\color{black}{(i, j)}$ 的色彩編號 $\color{black}{C_{ij}}$。


測資範圍:


$\color{black}{1≤ H, W ≤ 500}$


$\color{black}{1 ≤ S_i ≤ H}$


$\color{black}{1 ≤ S_j ≤ W}$


$\color{black}{0 ≤ Z ≤ 99}$


$\color{black}{0 ≤ C_{ij} ≤ 99}$

## 輸出說明

請輸出 $\color{black}{H}$ 行，每一行有 $\color{black}{W}$ 個非負整數，彼此以一個空白隔開，表示「填入色彩」$\color{black}{Z}$ 之後的新點陣圖 $\color{black}{P'}$。

## 範例輸入 #1

```
1 5 1 3 3
1 0 0 0 1
```

## 範例輸出 #1

```
1 3 3 3 1
```

## 範例輸入 #2

```
5 6 3 2 4
2 2 2 2 0 0
2 1 0 0 2 0
2 0 1 3 2 0
2 0 0 0 2 0
2 2 2 2 2 0
```

## 範例輸出 #2

```
2 2 2 2 0 0
2 1 0 0 2 0
2 4 1 3 2 0
2 4 4 4 2 0
2 2 2 2 2 0
```

## 範例輸入 #3

```
4 5 1 2 1
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
```

## 範例輸出 #3

```
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
```

## 範例輸入 #4

```
6 8 3 4 2
1 0 0 1 0 0 3 0
0 0 3 2 0 0 3 2
0 0 2 3 3 3 3 0
0 0 3 3 3 3 0 0
0 0 3 0 0 3 3 3
3 3 0 0 0 0 0 0
```

## 範例輸出 #4

```
1 0 0 1 0 0 2 0
0 0 3 2 0 0 2 2
0 0 2 2 2 2 2 0
0 0 2 2 2 2 0 0
0 0 2 0 0 2 2 2
3 3 0 0 0 0 0 0
```
