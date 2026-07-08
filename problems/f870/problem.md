# f870. DD換座位

## 內容

DD人物介紹 : https://zerojudge.tw/ShowProblem?problemid=f754


在DD王國裡，期中考剛考完，而DD中學的DD班只要考班排前十五名就能自己選位子。當然，DD每次都不能選，而正當DD很沮喪的時候，紅林出現了，紅林說 : 我的機會給你吧，就當作上次贏我的獎勵(題號 : f864)。對DD而言，這就跟頭皮屑消失一樣開心，從到了DD國中以來，他的目標只有三個，一是交女朋友，二是消除頭皮屑，三是自己選位子。今天他終於達成一項了，他終於可以跟心儀的對象Badspeed(D團的一員，東帝汶人)坐了，只不過，這次老師新增了換位子的規則，讓DD好想哭，好家在老師看他可憐給了DD一個權力。


請寫一個程式幫助DD，若你覺得DD不需幫助，請輸出"DD爛"，並獲得DD的回答。


規則如下 : 
有兩張班級座位表，第一張為原本的座位表，第二張為DD想要的座位表。要移動座位表必須全體一起移動。


往上移動 : 1 2 3             4 5 6        往下移動 : 1 2 3            7 8 9


                 4 5 6  ------>  7 8 9                         4 5 6  ----->  1 2 3


                 7 8 9             1 2 3                         7 8 9             4 5 6


 


往左移動 : 1 2 3             2 3 1        往右移動 : 1 2 3            3 1 2


                 4 5 6  ------>  5 6 4                         4 5 6  ----->  6 4 5


                 7 8 9             8 9 7                         7 8 9            9 7 8


 


 


往左旋轉 : 1 2 3             3 6 9       往右旋轉 : 1 2 3             7 4 1


                 4 5 6 ------>   2 5 8                        4 5 6 ------->  8 5 2


                 7 8 9             1 4 7                         7 8 9             9 6 3


DD的權利 : 
可使任意兩人交換位置，每筆測資只可用一次，用了步數要+1並且要輸出"DD thanks Honglin for his great kindness, DD will never forget it."(不含引號)。


 //DD thanks Honglin for his great kindness, DD will never forget it. 中文意思 : DD感謝紅林的大恩大德，DD永生難忘。

## 輸入說明

第一行有一整數 X ，代表有X筆測資。


第二行有四整數 M1，N1，M2，N2，代表班級座位表大小。 0<M1,M2,N1,N2<100


接著有兩張班級座位表。 // 座號皆為數字


第一張為原本的M1*N1大小的座位表。


第二張為DD想要的M2*N2大小的座位表。

## 輸出說明

請輸出最少要幾步才能達成DD的願望，若用了DD的權力，請輸出"DD thanks Honglin for his great kindness, DD will never forget it."(不含引號)，若無法達成，則輸出"Uh-oh, DD can't sit with Badspeed."(不含引號)。


// 無法達成不需輸出步數。

## 範例輸入 #1

```
1
3 3 3 3
1 2 3 
4 5 6
7 9 8
5 4 7
3 6 8
2 1 9
```

## 範例輸出 #1

```
3 DD thanks Honglin for his great kindness, DD will never forget it.
```

## 範例輸入 #2

```
1
3 4 4 3
7 8 9 1
10 11 5 12
2 3 4 6
12 6 1
5 4 2
11 3 8
10 9 7
```

## 範例輸出 #2

```
3 DD thanks Honglin for his great kindness, DD will never forget it.
```
