# a480. 導彈攔截系統

## 內容

某個國家研發了一套導彈攔截系統，只要設定了防護半徑 $\color{black}{r}$，在距離系統設置處 $\color{black}{r}$ 以內的範圍都會受到防護。此外，他們發現，啟用該系統會消耗大量的能源，且能源消耗為 $\color{black}{r^2}$。


在研發完成之際，敵國隨即向他們發射飛彈展開攻擊。不幸的是，該系統仍在試驗階段，所以目前僅設置於兩處 $\color{black}{(x_1, y_1)}$ 與 $\color{black}{(x_2, y_2)}$。由於能源消耗過於龐大，要使防護持久就必須讓能源消耗越小越好。因此，他們希望能以最少的能源消耗下防護境內所有的 $\color{black}{n}$ 個城市。


為了簡單起見，城市位置以一點 $\color{black}{(\xi_i, \eta_i)}$ 來表示。

## 輸入說明

$\color{black}{x_1}$ $\color{black}{y_1}$


$\color{black}{x_2}$ $\color{black}{y_2}$


$\color{black}{n}$


$\color{black}{\xi_1}$ $\color{black}{\eta_1}$


$\color{black}{\xi_2}$ $\color{black}{\eta_2}$


$\color{black}{\vdots}$


$\color{black}{\xi_n}$ $\color{black}{\eta_n}$



- $\color{black}{1\le n\le10^6}$。
- $\color{black}{-10^4\le x_1, y_1, x_2, y_2\le10^4}$。
- 對於所有的 $\color{black}{i \in \{1, 2, \ldots, n\}}$，均有 $\color{black}{-10^4\le\xi_i, \eta_i\le10^4}$。
- $\color{black}{(x_1, y_1)\ne(x_2, y_2)}$。
- 對於所有的 $\color{black}{i, j \in \{1, 2, \ldots, n\}}$，若 $\color{black}{i\ne j}$，則 $\color{black}{(\xi_i, \eta_i)\ne(\xi_j, \eta_j)}$。
- 輸入的數皆為整數。

## 輸出說明

$\color{black}{p}$
- $\color{black}{p}$ 為一整數，代表達成城市防護的能源消耗最小值。

## 範例輸入 #1

```
0 0
0 2
4
0 3
1 -1
1 0
1 1
```

## 範例輸出 #1

```
3
```
