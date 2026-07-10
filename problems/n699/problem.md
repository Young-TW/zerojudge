# n699. 00300 - Maya Calendar

## 內容

在他最近的學術休假期間，M. A. Ya 教授對古瑪雅曆法有了驚人的發現。根據一個古老的結繩記事，教授發現瑪雅文明使用了一種長達365天的年曆，稱為Haab，它有19個月。前18個月每個月有20天，這些月份的名字依次是：pop、no、zip、zotz、tzec、xul、yoxkin、mol、chen、yax、zac、ceh、mac、kankin、muan、pax、koyab、cumhu。每個月的日子不是用名字，而是用數字表示，從0到19。Haab的最後一個月叫uayet，這個月有5天，用數字0、1、2、3、4表示。瑪雅人認為這個月是不吉利的，法院不開庭，貿易停止，人們甚至不掃地。


出於宗教目的，瑪雅人使用了另一種曆法，稱為Tzolkin（神聖年）。這種曆法將一年分為十三個周期，每個周期有20天。每一天由一個數字和一天的名字組成。他們使用了20個名字：imix、ik、akbal、kan、chicchan、cimi、manik、lamat、muluk、ok、chuen、eb、ben、ix、mem、cib、caban、eznab、canac、ahau，並且這些名字和13個數字都在周期中循環。


注意，每一天都有一個唯一的描述。例如，在一年的開始，日子描述如下： 1 imix, 2 ik, 3 akbal, 4 kan, 5 chicchan, 6 cimi, 7 manik, 8 lamat, 9 muluk, 10 ok, 11 chuen, 12 eb, 13 ben, 1 ix, 2 mem, 3 cib, 4 caban, 5 eznab, 6 canac, 7 ahau, 然後在下一個周期繼續8 imix, 9 ik, 10 akbal...


年份（包括Haab和Tzolkin）用數字0, 1, ...表示，其中數字0是世界的開始。因此，第一天是： Haab: 0. pop 0 Tzolkin: 1 imix 0


請幫助 M. A. Ya 教授寫一個程序，將日期從 Haab 曆轉換為 Tzolkin 曆。

## 輸入說明

Haab日期的格式如下： NumberOfTheDay. Month Year


輸入文件的第一行包含輸入日期的數量。接下來的 n 行包含 n 個 Haab 日曆格式的日期，每個日期各佔一行。年份小於 5000。

## 輸出說明

Tzolkin日期的格式如下： Number NameOfTheDay Year


輸出文件的第一行包含輸出日期的數量。接下來的 n 行是 Tzolkin 日曆格式的日期，順序與輸入日期對應。

## 範例輸入 #1

```
3
10. zac 0
0. pop 0
10. zac 1995
```

## 範例輸出 #1

```
3
3 chuen 0
1 imix 0
9 cimi 2801
```
