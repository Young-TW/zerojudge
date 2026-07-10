# c093. 00608 - Counterfeit Dollar

## 內容

Sally 有一打銀幣（十二個），可是只有11個是真的，有一個是假的（但是它的顏色和大小都和真的一樣）。還好那個假幣的重量和真的不一樣，不過 sally   不知道它到底是比真的輕還是重。

  可喜的是， sally   有個朋友借他一個非常精準的天平，那個朋友同意讓 Sally   秤三次來找出假幣。例如，秤2個硬幣，結果天平平衡，那麼這2個都是真的。如果用其中的一個真的和第三個硬幣去秤，如果天平不平衡，那麼    sally就知道第三個硬幣是假的。同時他也可以根據天平來判斷那個假的到底是比真的輕還是重。Sally   會小心的選擇秤重的方法，這樣他才能用剛好秤三次找出那個硬幣是假的。

## 輸入說明

輸入的第一列有一個整數 n，代表以下有幾組測試資料。

                      每組測試資料三列，每列代表一次秤重。Sally   把他的硬幣編號為A～L。每次秤重左右兩邊的硬幣用2個字串表示（Sally   總是在左右兩邊放相同數目的硬幣），秤重的結果用 up, down,   even 來表示，代表天平的右邊是往上，往下，還是平衡。請參考Sample Input。

## 輸出說明

對每一組測試資料輸出哪一個硬幣是假的，並且是較輕還是較重。請注意：答案一定是唯一的。輸出格式請參考Sample   Output。

## 範例輸入 #1

```
2
ABCD EFGH even
ABCI EFJK up
ABIJ EFGH even
ABC DEF up
GHI JKL even
EF DA up
```

## 範例輸出 #1

```
K is the counterfeit coin and it is light.
D is the counterfeit coin and it is light.
```
