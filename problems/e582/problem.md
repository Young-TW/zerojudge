# e582. 00555 - Bridge Hands

## 內容

許多撲克牌遊戲都需要向4位玩家發牌，發完牌後每個人會有13張牌。
有的玩家可以不整牌直接玩，但是大多數玩家都需要整牌。
整牌首先按花色排序，花色順序為：
C = Clubs♣ < D = Diamonds♢ < S = Spades♠ < H = Hearts♡ 
再來按照點數大小排序，點數順序為：
2 < 3 < 4 < 5 < 6 < 7 < 8 < 9 < T < J < Q < K < A
玩家的座位分為北N，東E，南S，西W。其中一位玩家將被指定為發牌人，他向每個玩家分發一張牌，從左手邊的玩家開始，然後順時針進行發牌。
請你寫一個程式，該程式將讀取一副撲克牌的順序，並將其發給4位玩家。



![image](ShowImage?id=4055)

## 輸入說明

輸入包含多組測資。
每組測資第一行為一個字元(N，E，S，W)，代表發牌人坐的方位。
如果該字元為'#'，代表輸入結束。
接下來二行為一副撲克牌順序。

## 輸出說明

對於每組測資輸出四行。
分別代表4位玩家排列好的手牌，每張手牌請用空白分隔。
輸出玩家順序為(S、W、N、E)。
請參考範例輸出。

## 範例輸入 #1

```
N
CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3
DQS9SQDJH8HAS2SKD4H4S5C7SJC8DKC5C2CAHQCJSTH6HKH9D5HJ
#
```

## 範例輸出 #1

```
S: C3 C5 C7 CT CJ D9 DT DJ S3 SK H2 H9 HT
W: C2 C4 CK D4 D5 D6 DQ DA S4 S8 ST SJ H8
N: C6 C8 C9 CA D8 S9 SA H4 H5 H6 H7 HJ HA
E: CQ D2 D3 D7 DK S2 S5 S6 S7 SQ H3 HQ HK
```
