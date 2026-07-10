# a252. Another LCS

## 內容

一般LCS問題( Longest Common subsequence, 最長共同子字串)就是給定兩個字串，求出他們的LCS。為了理解這裡子字串定義，舉例來說，對於字串

  abccdda

          abc、adda、aca、bda等都是它的子字串，但adc、bdde、bddd等不是他的子字串。

          對於兩個字串accbbeffg、fcebg，他們的LCS長度為 3，而LCS為cbg或ceg。

          現在我們把問題弄得難一點，給三個字串，請求出他們的LCS長度為多少？

## 輸入說明

每個測資檔僅包含一筆測資，每筆測資有三個字串。測資保證三個字串的長度都不超過100，而且字串皆由小寫字母組成。

## 輸出說明

對每筆測資，輸出LCS的長度。

## 範例輸入 #1

```
abe
acb
babcd
```

## 範例輸出 #1

```
2
```
