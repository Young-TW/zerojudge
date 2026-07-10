# d047. 10070 - Leap Year or Not Leap Year and ...

## 內容

Gulamatu 這個古老的民族擁有非常先進的曆制。他們了解什麼是閏年 (可以被 4 整除但不能被 100 所整除的年份為閏年，但是可以被 400 所整除的年份仍為閏年。) 而且他們還有類似的節慶年。其中一個是 Huluculu 節 (發生於可被 15 整除的年份) 及 Bulukulu 節 (發生於可被 55 整除而且是閏年的年份)。給你一個年份，你要說出這年有什麼特性。如果這年既非閏年，也非節慶年，就印一行「This is an ordinary year.」。這些特性要以下列的順序印出來：閏年-->huluculu-->bulukulu。

## 輸入說明

會有很多年份作為輸入。每年單獨一行。輸入以 end of file 作為結束。所有的年份不會小於 2000 (以規避早年不同的閏年規則)。請勿作任何其它的假設。

## 輸出說明

相對於每個輸入，你要根據上述規則及範例輸出列出這個年份的所有不同特性，每種特性一行。每個年份的輸出請以空行隔開。請注意共有四種不同的特性。

## 範例輸入 #1

```
2000
3600
4515
2001
```

## 範例輸出 #1

```
This is leap year.

This is leap year.
This is huluculu festival year.

This is huluculu festival year.

This is an ordinary year.
```
