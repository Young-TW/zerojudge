# i322. 經典河內塔

## 內容

河內之塔 (Towers of Hanoi) 是法國人 M. Claus (Lucas) 於 1883 年從泰國帶至法國的，河內為越南的首都。1883年法國數學家 Edouard Lucas 曾提及這個故事，據說創世紀時 Benares 有一座波羅教塔，是由三支鑽石棒 (Peg) 所支撐，開始時神在第一根棒上放置 64 個由上至下依由小至大排列的金盤 (Disc)，並命令僧侶將所有的金盤從第一根石棒移至第三根石棒，且搬運過程中遵守大金盤在小金盤之下的原則，若每日僅搬一個金盤，則當金盤全數搬運完畢之時，此塔將毀損，而也就是世界末日來臨之時。


以下是一個河內塔的遊戲，你可以玩玩看。


https://webgamesonline.com/towers-of-hanoi/index.php

## 輸入說明

輸入只有一行，含有一個正整數 𝑛 (1 ≤ 𝑛 ≤ 15)，代表金盤的數量。

## 輸出說明

請輸出把 A 上 𝑛 個金盤移動到 C 的方法。


金盤的編號由小到大依序為 1 ~ 𝑛。三支鑽石棒的代號則為 A, B, 和 C。

## 範例輸入 #1

```
2
```

## 範例輸出 #1

```
Move disc 1 from A to B
Move disc 2 from A to C
Move disc 1 from B to C
```

## 範例輸入 #2

```
3
```

## 範例輸出 #2

```
Move disc 1 from A to C
Move disc 2 from A to B
Move disc 1 from C to B
Move disc 3 from A to C
Move disc 1 from B to A
Move disc 2 from B to C
Move disc 1 from A to C
```
