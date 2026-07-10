# b775. 10028. Fast Page Rank

## 內容

每一個網站都有超連結 (hyperlink) 到另一個網站，該網站會將自己的 Page Rank Value 均勻分配給連出去的網站。當一個網站被連接的次數越多，則網站的 Page Rank 越高。


將 $N$ 個網站之間的關係轉為 Graph，計算轉換成馬可夫過程。但馬可夫過程容易造成 Page Rank 失算，因為有些點並沒有出度 (連接到別的網站)，數值就會隨著迭代集中到這個孤島上 (或者說蜘蛛網)，造成其他點的 Page Rank 皆為 0。為了防止這一點，給予 Page Rank 的總和 $N$。轉移只有 $\alpha$ 的信任度，剩餘的 $1 - \alpha$ 將隨機選擇全局的網站進行轉移。


例如



```
1: 2, 3, 4
2: 3, 4
3: 4
4: 2
```

$$
S_{n \times n} = \begin{bmatrix}
0 & 0 & 0 & 0\\ 
1/3 & 0 & 0 & 1\\ 
1/3 & 1/2 & 0 & 0\\ 
1/3 & 1/2 & 1 & 0
\end{bmatrix}
$$


根據 $G = \alpha S + (1 - \alpha) \frac{1}{n} U, ; \alpha = 0.85$ 得到


$$
\beta = (1 - \alpha) / 4 = 0.375\\
G_{n \times n} = \begin{bmatrix}
0 \times 0.85 + \beta  & \beta & \beta & \beta \\ 
1/3 \times 0.85 + \beta & \beta & \beta & 1 \times 0.85 + \beta\\ 
1/3 \times 0.85 + \beta & 1/2 \times 0.85 + \beta & \beta & \beta\\ 
1/3 \times 0.85 + \beta & 1/2 \times 0.85 + \beta & 1 \times 0.85 + \beta & \beta
\end{bmatrix}
$$


假設 Page Rank Vector $q^{\text{cur}}$ 和 $q^{\text{next}}$ 分別表示當前求得的結果和下一次的迭代數值，則


$$ q^{\text{next}} = Gq^{\text{cur}} $$


不斷地迭代直到 $|\overrightarrow{q^{\text{next}}q^{\text{cur}}}| < \varepsilon$，其中 $\varepsilon = 10^{-10}$

## 輸入說明

有多組測資，每組測資第一行會有一個整數 $N$ 表示有多少個網站，接下來會有一個 $N \times N$ 的 0/1 矩陣，其中 $E_{i, j}$ 表示第 $i$ 個網站連到第 $j$ 個網站。


- $1 \le N \le 3000$

## 輸出說明

每組測資輸出一行，輸出每一個網站的 Page Rank Value，用空白隔開並保留兩位小數。

## 範例輸入 #1

```
4
0111
0011
0001
0100
```

## 範例輸出 #1

```
0.15 1.49 0.83 1.53 
```
