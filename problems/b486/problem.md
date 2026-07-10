# b486. 變態史考古

## 內容

題目描述隨著考古學者近幾年的研究，逐漸地分析出變態人類文化族群的祖先。同時也知道，每一代人會將其變態基因傳遞給下一代，而下一代的變態指數會比上一代多一。若子代有數個，每個子代帶有的變態性向會有所歧異。

每當新聞報導某個變態父子關係時，人們總會熱議某兩個變態的相似程度。口耳相傳的消息是不可信任的，現在給予事情發生的時間軸，請驗證人們口中的變態相似程度。

變態相似程度定義

$$\textit{sim}(A, B) = \frac{\textit{dist}(\textit{Original}(A), \textit{LCA}(A, B)) \times 2}{\textit{dist}(\textit{Original}(A), A) + \textit{dist}(\textit{Original}(B), B)}$$

其中 $\textit{Original}(A)$ 表示根據事實推測得到的最早源頭祖先，$\textit{dist}(A, B)$ 表示在樹狀圖中兩點的距離，$\textit{LCA}(A, B)$ 表示 $A, \; B$ 最小公共祖先 (Lowest Common Ancestor，簡稱 LCA)。

例如當前知道的祖先關係如下 

```
        P
       / 
      Q
     / \
    A   R
       /
      B

```
- $\textit{Original}(A) = \textit{Original}(B) = P$，
- $\textit{dist}(P, A) = 3, \; \textit{dist}(P, B) = 4, \; \textit{LCA}(A, B) = Q, \; \textit{dist}(Q, P) = 2$。
- 最後 $\textit{sim}(A, B) = \frac{4}{7}$

## 輸入說明

有多組測資，每一組第一行會有兩個整數 $N, M$，分別為變態人口總數、詢問次數，接下來會有 $M$ 行，每一行上會有兩種情況

- news x y  新聞報導 $x$ 的祖先是 $y$，保證每一篇新聞報導關於 $x$ 的祖先只會出現一篇，且不會出現矛盾情況。
- sim x y    計算變態相似程度 $\textit{sim}(x, y)$ 
約束條件

- $1 \le N, M \le 100000$
- $1 \le x, y \le N$
- 祖先的編號一定小於子代

## 輸出說明

對於每個詢問輸出一行，輸出最簡分數。若詢問 $x, y$ 完全沒有關係，則輸出 -1

## 範例輸入 #1

```
5 9
news 3 2
news 4 2
sim 3 4
sim 3 5
news 2 1
news 5 4
sim 3 4
sim 3 5
sim 4 4
```

## 範例輸出 #1

```
1/2
-1
2/3
4/7
1/1
```
