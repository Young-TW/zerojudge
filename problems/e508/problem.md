# e508. 11917 - Do Your Own Homework!

## 內容

這幾天Soha非常忙，以至於他沒有時間寫作業。
但這不是一個大問題，因為他有很多願意幫助他的朋友，其中一個就是Sparrow。
每當Soha被分配任何作業時，他都會向Sparrow尋求她的幫助。
Sparrow給出了她喜歡的科目列表，以及完成每個科目的作業所需的天數。
Soha只有 D 天的時間來完成他的作業。不過還好教授允許可以遲交最多 5 天。
這意味著教授將不接受從現在起 D+5 天之後的任何提交。
Sparrow這次能為Soha做到嗎？



![image](ShowImage?id=4043)

## 輸入說明

輸入的第一行是一個正整數T (T < 100)，代表Case數量。
每個Case的第一行為正整數N (1 <= N <= 100)，代表Sparrow可以接受的科目數量。
接下來的N行中，每行包含一個科目的名稱，完成該科目的所需天數。
所有科目名稱皆不相同。
接下來一行包含一個整數D (1 <= D <= 100)，表示Soha只有D日可以完成他的作業
下面一行包含需要繳交作業的科目名稱。
所有科目名稱均由小寫字母組成，且長度為1~20個字元。

## 輸出說明

對於每個Case輸出Case編號(如範例輸出)
如果Sparrow完成作業所需的時間不超過D天
輸出"Yesss"
如果她花了D天以上但不超過D+5天
輸出"Late"
如果她花了超過D+5天或者科目她不滿意
輸出"Do your own homework!"

## 範例輸入 #1

```
3
3
compiler 4
cplusplus 1
java 8
5
compiler
2
algorithm 3
math 9
4
math
2
java 8
ai 3
6
calculus
```

## 範例輸出 #1

```
Case 1: Yesss
Case 2: Late
Case 3: Do your own homework!
```
