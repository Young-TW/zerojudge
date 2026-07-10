# d671. 11716 - Digital Fortress

## 內容

I I U P C   2 0 0 9

上一屆的 IIUPC 有一題「達文西密碼」是以丹布朗的暢銷書「達文西密碼」為故事背景。這一題則是以科技驚悚小說「數位堡壘」為背景。題目給你一個密文，你要用下述的解碼方式來解碼。比如說，如果密文如下：
WECGEWHYAAIORTNU
輸出則是：
WEAREWATCHINGYOU

上例中所給的密文 "WECGEWHYAAIORTNU" 有 16 個字元，也就是 4 的平方。請把這些字元以「列優先」(row major，第一列放滿後再放第二列，再第三列……) 的方式置入一個 n ´ n (本例為 4 ´ 4) 的格子。本例密文放置完成後的格子如下：
W E C G
E W H Y
A A I O
R T N U

當我們以「行優先」(column major，取完第一行再取第二行，然後第三行) 的方式將上面格子的字元取出便可以得到以下的明文：
WEAREWATCHINGYOU

## 輸入說明

輸入的第一行有一個數字 T，接著有 T 筆測資，每筆測資一行，該行便是要處理的密文。密文僅包含大寫字母及空白。密文的總字元數不會超過 10,000。

## 輸出說明

相對於每筆測資，請將明文輸出於一行。若輸入的字元數不是完全平方數，請輸出「INVALID」。

## 範例輸入 #1

```
3
WECGEWHYAAIORTNU
DAVINCICODE
DTFRIAOEGLRSI TS
```

## 範例輸出 #1

```
WEAREWATCHINGYOU
INVALID
DIGITAL FORTRESS
```
