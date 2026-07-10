# c629. 魔法開端

## 內容

據說在成為大魔法師之前，$\color{black}{Aw}$ 只是位計程車司機。日復一日的工作使他困惑 ── 十餘年來為了接送旅客往返四方，自己人生的目的地又在哪兒呢？


這天，帶著迷惘上路， $\color{black}{Aw}$ 不知不覺來到一處岩壁，剎那間天搖地動，石塊滾滾而下。$\color{black}{Aw}$ 立即奔出車外，幸運地逃過一劫。回頭，縱使塵土飛揚，卻依稀可見岩壁上一道裂縫正微微透著奇異光芒 ── 那是個洞窟的入口，他決定前去一探究竟。


貓有九命，然而好奇心能殺死一隻貓。入口在 $\color{black}{Aw}$ 踏進洞窟的同時闔上並冒出烈燄，逐漸朝他延燒，而洞窟另一頭有扇雕紋精美的木門，上面鋪著藍與黑的圖案。木門似乎是唯一出路，只不過門把轉也轉不動。此時， $\color{black}{Aw}$ 的腦中湧現無數自己從未接觸過的知識：藍黑色圖案是基礎魔法咒文，可分別以 $\color{black}{n * n}$ 的特殊方陣 $\color{black}{A, B}$ 分析。


基礎魔法的方陣 $\color{black}{A, B}$ 必能以特定的 $\color{black}{s, a, c}$ 生成。首先將 $\color{black}{s}$ 填入左上角，接著逐次向右移動一格（超出邊界時移到下一列最左邊的格子），並填入 $\color{black}{a * (上個格子的數值) + c}$。


咒文疊加後能交織成更強大的複合魔法，其方陣即為各個基礎魔法方陣的乘積，例如木門上的魔法可寫作 $\color{black}{C = A * B}$ ，其中 $\color{black}{C_{ij} = \displaystyle \sum_{k=0}^{n - 1}{A_{ik} * B_{kj}}}$，注意到這裡方陣的行列編號使用 $\color{black}{0 \sim n - 1}$。
在火焰吞噬整個洞窟以前，$\color{black}{Aw}$ 必須求得若干個 $\color{black}{C_{ij}}$ 的數值好讓他攻擊魔法的弱點，為了確定自己計算無誤，他透過某種方式向你求助，希望你告訴他 $\color{black}{C_{ij}}$ 除以 $\color{black}{10^9+7}$ 的餘數。

## 輸入說明

首行有兩個正整數 $\color{black}{n, \space q \space (1 \le n \le 10^9, \space 1 \le q \le 500000)}$ 代表方陣大小及詢問數量。


第二行為用以生成方陣 $\color{black}{A}$ 和 $\color{black}{B}$ 的整數 $\color{black}{s_A, \space a_A, \space c_A, \space s_B, \space a_B, \space c_B \space (0 \le s, \space a, \space c < 10^9+7)}$。


接下來 $\color{black}{q}$ 行分別有兩個整數 $\color{black}{i, \space j \space (0 \le i, \space j < n)}$ 代表詢問位置。

## 輸出說明

對於每次詢問，輸出 $\color{black}{C_{ij} \space \% \space (10^9+7)}$ 的值於一行。

## 範例輸入 #1

```
3 9
1 1 2 10 0 0
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
```

## 範例輸出 #1

```
10
0
0
70
0
0
130
0
0
```
