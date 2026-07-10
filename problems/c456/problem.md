# c456. 5. 馬拉松

## 內容

金氏運動公司打算舉辦一場馬拉松比賽，為了締造亮眼的完成比賽時間，金氏運動公司打算選擇性地邀請選手參賽。分析過往的數據資料，金氏運動公司觀察到以下二個現象：



(a) 對於任何一位選手，如果愈多他的朋友參賽，則他就能跑得愈快，所以傾向於找一群選手使得彼此互相認識的情況很多。因為認識是雙向的，如果 $\color{black}{P}$ 認識 $\color{black}{Q}$，則 $\color{black}{Q}$ 認識 $\color{black}{P}$。所以當我們說 $\color{black}{P}$ 認識 $\color{black}{Q}$ 時，等同於表示 $\color{black}{P}$、$\color{black}{Q}$ 兩位互相認識。


(b) 如果參賽的選手當中，存在兩位選手 $\color{black}{P}$ 和 $\color{black}{Q}$ 彼此不認識，而且在參賽的選手當中無法找到 $\color{black}{t}$ 位選手 $\color{black}{S_1、\ldots、S_t}$ ($\color{black}{t}$ 為任意大於 $\color{black}{0}$ 的整數)，使得 $\color{black}{P}$ 認識 $\color{black}{S_1}$，$\color{black}{S_1}$ 認識$\color{black}{S_2}$，$\color{black}{\ldots}$，$\color{black}{S_{t-1}}$ 認識 $\color{black}{S_t}$，$\color{black}{S_t}$ 認識 $\color{black}{Q}$，則比賽將會有嚴重的惡性競爭，所以需要避免這樣的狀況。


現在金氏運動公司手上有一份 $\color{black}{N}$ 位選手的名單以及一份顯示這 $\color{black}{N}$ 位選手彼此之間是否認識的表單，現在的任務是從這 $\color{black}{N}$ 位選手找出選手的子集合 $\color{black}{S = \{P_1, P_2, \ldots, P_{\left\lvert S \right\rvert}\}}$，使得 $\color{black}{S}$ 沒有惡性競爭的狀況，而且讓以下影響因子 $\color{black}{F(S)}$ 得到最大化，這影響因子的設計除了讓每位選手都認識夠多的參賽者，也兼顧了不讓參賽人數過少。


$\color{black}{F(S) = \left\lvert S \right\rvert min_{1 \le i \le \left\lvert S \right\rvert}D_i}$，


其中 $\color{black}{D_i}$ 表示選手 $\color{black}{P_i}$ 所認識的人當中，有多少人在子集合 $\color{black}{S}$ 裡面。 在以下這個 $\color{black}{4}$ 位選手的例子中，選 $\color{black}{S = \{2, 3, 4\}}$ 比其他的選法有更高的 $\color{black}{F(S)}$。



![image](ShowImage?id=1057)

## 輸入說明

每一組測試資料有兩列， 其中第一列有兩個正整數 $\color{black}{N}$ 和 $\color{black}{M (1 \le M \le N*(N-1)/2)}$，
第二列有 $\color{black}{M}$ 對正整數 $\color{black}{X_1\ Y_1\ X_2\ Y_2\ \ldots\ X_M\ Y_M}$，代表選手 $\color{black}{X_i}$ 認識選手 $\color{black}{Y_i (1 \le i \le M}$ 且 $\color{black}{1 \le X_i \lt Y_i \le N)}$。

## 輸出說明

對於每組測試資料，輸出最大的 $\color{black}{F(S)}$。$\color{black}{F(S)}$ 這數字需獨自佔一列。

## 範例輸入 #1

```
輸入範例 1：
4 5
1 2 2 3 3 4 4 1 2 4

輸入範例 2：
4 4
1 2 2 3 3 4 2 4

輸入範例 3：
6 6
1 3 1 2 2 3 4 5 5 6 4 6
```

## 範例輸出 #1

```
輸出範例 1：
8

輸出範例 2：
6

輸出範例 3：
6
```
