# a130. 12015 - Google is Feeling Lucky

## 內容

Google 為最有名的網路搜尋引擎之一，它也提供許多網路服務與產品。在它的搜尋首面上有一個有趣的按鈕「好手氣」吸引了我們的目光。這個功能讓使用者跳過搜尋結果頁面而直接進入排名最高的頁面。真是省時又好用！

問題是，當按下「好手氣」時到底會出現哪一個頁面？Google 有個不錯的方式來處理。為了簡化問題，假設 Google 為每個頁面設定了一個整數的相關度。相關度最高的頁面就會中選。如果平分，所有的相關度最高的頁面都有可能中選。

給你 10 個頁面及相關度，請選出所有可能成為「好手氣」的頁面。

## 輸入說明

輸入有多筆測資。輸入的第一行有測資的筆數 T。每筆測資中有 10 行以描述頁面及相關度。每行含有一個不含空白的字串代表頁面的網址及一個整數 Vi 代表該頁面的相關度。網址的長度介於 1 到 100 之間(含)。( 1 <= Vi  <= 100)

## 輸出說明

對於每筆測資，輸出可能中選的頁面網址。網址出現的順序與輸入相同。輸出格式請參考輸出範例。

## 範例輸入 #1

```
2
www.youtube.com 1
www.google.com 2
www.google.com.hk 3
www.alibaba.com 10
www.taobao.com 5
www.bad.com 10
www.good.com 7
www.fudan.edu.cn 8
www.university.edu.cn 9
acm.university.edu.cn 10
www.youtube.com 1
www.google.com 2
www.google.com.hk 3
www.alibaba.com 11
www.taobao.com 5
www.bad.com 10
www.good.com 7
www.fudan.edu.cn 8
acm.university.edu.cn 9
acm.university.edu.cn 10
```

## 範例輸出 #1

```
Case #1:
www.alibaba.com
www.bad.com
acm.university.edu.cn
Case #2:
www.alibaba.com
```
