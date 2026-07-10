# i589. Forbidden Cities

## 內容

There are $n$ cities and $m$ roads between them. Kaaleppi is currently in city $a$ and wants to travel to city $b$.


However, there is a problem: Kaaleppi has recently robbed a bank in city $c$ and can't enter the city, because the local police would catch him. Your task is to find out if there is a route from city $a$ to city $b$ that does not visit city $c$.


As an additional challenge, you have to process $q$ queries.


有 $n$ 個城市，以 $m$ 條雙向道路連接。肯肯肯在城市 $a$，並且他想到達城市 $b$。


但是有一個問題：肯肯肯最近在城市 $c$ 搶銀行了，被當地的警察通緝，於是他無法到達城市 $c$。你要幫肯肯肯找出有沒有一條由 $a$ 到 $b$，且不經過城市 $c$ 的路徑。


你總共要處理 $q$ 次詢問。(不保證 $a ≠ b, b ≠ c, c ≠ a$，儘管原題敘有說它們會相異，但還是出現了不相異的測資)

## 輸入說明

第一行有三個正整數 $n, m, q$，代表有 $n$ 個城市，$m$ 條道路，$q$ 筆詢問。城市編號為 $1\sim n$。


接下來 $m$ 行，每行有兩個正整數 $a, b$，代表城市 $a, b$ 之間有一條雙向道路。


接下來 $q$ 行，每行有三個正整數 $a, b, c$，代表詢問你是否有一條連接 $a, b$ 的路徑可以不經過 $c$。


你可以假設每個城市都可以互相到達。


- $1 \leq n \leq 10^5$
- $1 \leq m \leq 2 \times 10^5$
- $1 \leq q \leq 10^5$
- $1 \leq a, b, c \leq n$

## 輸出說明

對於每筆詢問，如果存在一條路徑，輸出 $\text{YES}$，否則輸出 $\text{NO}$。

## 範例輸入 #1

```
5 6 3
1 2
1 3
2 3
2 4
3 4
4 5
1 4 2
3 5 4
3 5 2
```

## 範例輸出 #1

```
YES
NO
YES
```
