# q890. 1727 - Counting Weekend Days

## 內容

The contestants probably don't know how eagerly problem-setters wait for the weekend to make problems that would terrorize contestants. So before a month begins, some problem-setters try to calculate the number of weekend days in that month and plan accordingly, can you help them?


There are seven days in a week namely Sunday (SUN), Monday (MON), Tuesday (TUE), Wednesday (WED), Thursday (THU), Friday (FRI) ,and Saturday (SAT). There are twelve months in a year, January (JAN), February (FEB), March (MAR), April (APR), May (MAY), June (JUN), July (JUL), August (AUG), September (SEP), October (OCT), November (NOV) and December (DEC). These months have 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 and 31 days respectively.  February has 29 days in a leap year(which we won't discuss). Unlike other countries, Friday (FRI) and Saturday (SAT) are considered weekend days in Bangladesh. Given a month and the name of the first day of that month, you will have to find out the total no of weekend days in that month.


給定月份和該月第一天之星期，求該月週末天數（週五及週六）

## 輸入說明

First line contains an integer T (T ≤ 100) which denotes the number of test cases. The input for each set is given in a single line. This line contains two strings MTH and DAY, which is the three digit code shown previously.


首行有一整數T，代表測資行數(T≤100)
接下來T行，每行有兩用空白分開之字串
(分別代表月份和該月第一天之星期之簡寫)

## 輸出說明

For each line of input produce one line of output. It contains a single integer which denotes the number of weekend days (Friday and Saturday) in that month. You must do your calculation assuming that the year is not a leap year.


輸出該月週末天數（週末為週五及週六）
#一律不考慮閏年

## 範例輸入 #1

```
3
JAN SUN
FEB SUN
OCT THU
```

## 範例輸出 #1

```
8
8
10
```
