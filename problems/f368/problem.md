# f368. 迦壕的回家作業

## 內容

迦壕有色弱，所以有些顏色他分不清楚，這裡假設是紅色(RED)和綠色(GREEN)


這個問題一直困擾著他，像是寫功課時，迦壕想要把一個句子寫下來，但是句子裡若有"RED"或"GREEN"時，他就會分不清楚，進而導致寫錯


這時候他只能猜答案，假設猜紅色(RED)和綠色(GREEN)的機率均等


今天給你一個英文的句子，均是大寫(無空白)，請輸出迦壕猜對的機率



![image](ShowImage?id=1625)

## 輸入說明

有多行(EOF結束)


每行有一個英文字串，均是大寫(無空白)

## 輸出說明

每行輸出的形式為1/n，代表猜對的機率

## 範例輸入 #1

```
HELLO
REDREDRED
GREENNREDD
REDGREENREDDERNEERG
ABCDEFGREENHIJKLMNOPQREDSTUVWXYZ
```

## 範例輸出 #1

```
1/1
1/8
1/4
1/8
1/4
```
