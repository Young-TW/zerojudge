# f980. Ｗｉtｈoｕt　Ｍｅ

## 內容

![image](ShowImage?id=1794)


"Now this looks like a job for me.
So everybody, just follow me.
Cause we need a little, controversy.
Cause it feels so empty, without me."


有一個小男孩在唱片行買了一個印有 "Parental Advisory" 的專輯，幸好 Ǝ-Man 和 D博士 及時阻止小男孩播放。


唱片行架子上的歌曲都要排序，排序有很多種 (可見 Youtube 和 Youtube)


有Bubble Sort、Selection Sort、Merge Sort


甚至還有概念上 O(1) 的 Gravity Sort


不過 Caido 最喜歡的，當然還是 Bogo Sort 了 (可見 Youtube)


Bogo Sort 就是隨便排，直到排對為止，平均複雜度有 O(n*n!)，最壞可以到無限


但如果 Caido 每次運氣都很好，一次就能排序成功，複雜度就能變 O(n) 欸 !!


O(n) 已經比幾乎所有排序方法還要好了，於是 Caido 決定向全世界推廣 Bogo Sort !


經過某些秘密情報，全球百分之 99.7 的網路公司在 2030 年都要把排序法全部改成 Bogo Sort，來提升電腦運算效率，連某些實驗室在研發的超級電腦、量子電腦，使用的排序法都要採用 Bogo Sort


由上可知 Bogo Sort 在市場裡的潛力了，Caido 也打算要研究自己的 Bogo Sort ，只是Caido要先解決一些基本的問題，就是有 n 個相異的數字要進行 Bogo Sort，一次就成功的機率為多少？


假設答案為 1/ans，請輸出 ans

## 輸入說明

每行輸入 n, P，( n的位數≤10000，P 為一質數，2≤ P ≤10007 )

## 輸出說明

輸出 ans


(因為答案可能很大，請 mod P 後再輸出)

## 範例輸入 #1

```
116 6733
881 4073
881 8803
521 9539
867 877
```

## 範例輸出 #1

```
2896
763
2968
7738
31
```
