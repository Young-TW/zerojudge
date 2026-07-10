# d133. 00357 - Let Me Count The Ways

## 內容

經過在百貨公司的一場血拼之後，小梅發現她身上的零錢共有17分（cent，美金貨幣單位，其他貨幣及面值請參考下方紅字部分），分別是1個dime，1個nickel，以及2個penny。隔天，小梅去便利商店買完東西後發現她身上的零錢恰好又是17分，這次是2個nickel及7個penny。小梅就在想，有幾種硬幣的組合可能湊成17分呢？經過仔細算算之後，發現共有6種。

你的問題就是：給一個金額，請你回答共有多少種硬幣組合的方式。

p.s 美國的零錢共有以下幾種硬幣以及其面值：

- penny, 1 cent 
- nickel, 5 cents 
- dime, 10 cents 
- quarter, 25 cents 
- half-dollar, 50 cents

## 輸入說明

每組測試資料1列，有1個整數n（0 <= n <=30000），代表零錢的總金額。

## 輸出說明

對每組測試資料請輸出共有多少種硬幣組合方式。輸出格式為以下2種其中之一。

- There are m ways to produce n cents change. 
- There is only 1 way to produce n cents change.

## 範例輸入 #1

```
17 
11
4
```

## 範例輸出 #1

```
There are 6 ways to produce 17 cents change. 
There are 4 ways to produce 11 cents change. 
There is only 1 way to produce 4 cents change.
```
