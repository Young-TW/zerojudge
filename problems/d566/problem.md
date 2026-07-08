# d566. 秒殺率

## 內容

大韜自從成為題目管理員以後，
便積極的把平時靈機一動的想法出成題目上傳到ZeroJudge。
但是他出的題目太簡單了，
題目總是通過率百分之百！

有一天他查看解題紀錄的時候發現，
同樣通過率百分之百的兩個題目，
有的會讓使用者第一次就AC，
而其他可能大部分使用者會有幾次嘗試發生WA、NA以後才會AC。

我們定義：
「如果一個使用者在第一次Submit就AC一個題目，就是他"秒殺"了這題」。
現在有一張從ZeroJudge上擷取的解題紀錄表，
而「秒殺率 = 秒殺人數÷AC人數」，
大韜想請你分析一下這題的秒殺率是多少？

## 輸入說明

共計四個測資點，每個測資點只有一組測試資料。

第一行有整數n(1<=n<=10000)，表示接下來的解題紀錄表有n行。
從第二行開始，每行有"解題者帳號"<空格>"解題狀況"。
解題者帳號由小於30字元的大寫字母、小寫字母、數字組成，並且大小寫視為不同。
解題狀況則有AC、NA、WA、TLE、CE五種
並且請注意，此處的解題紀錄"排在前面"的資料代表時間"越晚"(與ZJ實際狀況同)

## 輸出說明

請輸出秒殺人數÷AC人數，以百分比為單位。
(保證輸出的百分比會是整數，並且AC人數必定大於0)

## 範例輸入 #1

```
30
BonBon CE
BonBon CE
BonBon CE
duckingod AC
duckingod AC
BonBon CE
BonBon CE
BonBon CE
BonBon CE
BonBon CE
e196819 TLE
e196819 NA
ws124310 AC
BonBon CE
BonBon CE
BonBon CE
BonBon CE
ws124310 NA
duckingod AC
BonBon CE
BonBon CE
BonBon CE
duckingod AC
duckingod AC
ws124310 NA
ws124310 TLE
e196819 CE
e196819 TLE
e196819 AC
jack1 AC
```

## 範例輸出 #1

```
75%
```
