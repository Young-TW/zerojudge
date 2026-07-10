# e653. 10490 - Mr. Azad and his Son!!!!!

## 內容

在孟加拉，Abul Kalam Azad是一個很厲害的人。但是，為什麼他如此特別？並不只是因為他是我父親。而是他可以出色地進行一些計算。
如果有人給他任何正整數k，那麼他可以驚人地說出相對完美的數字(2^(k-1))*(2^k - 1)，而無需使用計算機或電腦。
例如，我告訴他k = 2時相對完美的數字是多少，他馬上回答是6。
我詢問他是如何計算得這麼迅速的，但是他說我應該自己想辦法，想想一個整數與一個完美數有什麼關聯。
儘管我不知道他怎麼做，但我知道下一屆ACM競賽即將到來，世界頂尖的高手可以解決我非常簡單的問題。
現在，您要為我寫一個程式來贏得我的父親，該程式將判斷經過p = (2^(k-1))*(2^k - 1)計算後，p是否為完美數。

## 輸入說明

輸入有多行，每行一個整數k (1 < k ≤ 31)。
如果k = 0代表輸入結束。

## 輸出說明

對於每行輸出如下：
若p為完美數，輸出：
"Perfect: p!"
若p不為完美數，且k為質數，輸出：
"Given number is prime. But, NO perfect number is available."
若p不為完美數，且k不為質數，輸出：
"Given number is NOT prime! NO perfect number is available."

## 範例輸入 #1

```
2
3
6
0
```

## 範例輸出 #1

```
Perfect: 6!
Perfect: 28!
Given number is NOT prime! NO perfect number is available.
```
