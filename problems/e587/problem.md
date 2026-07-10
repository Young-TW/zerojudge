# e587. 10530 - Guessing Game

## 內容

Stan和Ollie在玩猜數字遊戲。Stan選擇一個正確答案，答案介於1到10之間，Ollie猜數字可能是多少。
每次猜測之後，Stan都會說Ollie的猜測是太高，太低還是正確。
在玩了幾輪之後，Ollie開始懷疑Stan在作弊，也就是說，在Ollie猜測時，Stan把正確答案換了。
為了準備"吉"Stan，Ollie紀錄了幾場比賽內容。
您你工作就是確定每個比賽內容是否證明Stan在作弊。

## 輸入說明

輸入包含多場比賽內容。
每場比賽內容由成對的猜測和回答組成。
猜測為一個數字x，x介於1到10之間。
回答包含"too high"、"too low"、"right on"。
每場比賽以"right on"結尾。
最後一場比賽內容為一個0，代表輸入結束。

## 輸出說明

對於每場比賽內容
如果Stan的回答與正確答案不一致
輸出"Stan is dishonest"
否則
輸出"Stan may be honest"

## 範例輸入 #1

```
10
too high
3
too low
4
too high
2
right on
5
too low
7
too high
6
right on
0
```

## 範例輸出 #1

```
Stan is dishonest
Stan may be honest
```
